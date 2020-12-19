import React, {useState} from 'react';
import {render} from 'react-dom';
import {StaticMap} from 'react-map-gl';
import DeckGL from '@deck.gl/react';
import {GeoJsonLayer, PolygonLayer} from '@deck.gl/layers';
import {LightingEffect, AmbientLight, _SunLight as SunLight} from '@deck.gl/core';
import {scaleSequential} from 'd3-scale';
import {interpolateOrRd} from 'd3-scale-chromatic';
import {readString} from "react-papaparse";

// "MapboxAccessToken" 환경변수값
const MAPBOX_TOKEN = process.env.MapboxAccessToken; 

export const COLOR_SCALE = x =>
  // https://github.com/d3/d3-scale-chromatic
    (
      scaleSequential()
      .domain([0, 4]) // 밀도 최대 4명
      .interpolator(interpolateOrRd)
    )(x) // return a string color "rgb(R,G,B)"
    .slice(4,-1)  // extract "R,G,B"
    .split(',') // spline into an array ["R", "G", "B"]
    .map(x => parseInt(x,10));  // convert to [R, G, B]


const INITIAL_VIEW_STATE = {
  // 서울시청 좌표
  latitude: 37.5663,
  longitude: 126.9779,
  zoom: 11,
  maxZoom: 16,
  pitch: 45,
  bearing: 0
};

const ambientLight = new AmbientLight({
  color: [255, 255, 255],
  intensity: 1.0
});

const dirLight = new SunLight({
  timestamp: Date.UTC(2019, 7, 1, 22),
  color: [255, 255, 255],
  intensity: 1.0,
  _shadow: false
});

function getTooltip({object}) {
  return (
    object && {
      html: `\
      <div><b>${object.properties.adm_nm}</b></div>
      <div>총 어린이집 수: ${object.properties.population.total.toLocaleString()} </div>
      <div>국공립: ${object.properties.population.total_a.toLocaleString()} </div>
      <div>사회복지법인: ${object.properties.population.total_b.toLocaleString()} </div>
      <div>법인,단체 등: ${object.properties.population.total_c.toLocaleString()} </div>
      <div>민간: ${object.properties.population.total_d.toLocaleString()} </div>
      <div>가정: ${object.properties.population.total_e.toLocaleString()} </div>
      <div>부모협동: ${object.properties.population.total_f.toLocaleString()} </div>
      <div>직장: ${object.properties.population.total_g.toLocaleString()} </div>
      <div>신혼: ${object.properties.population.newMarry.toLocaleString()} </div>
    `
    }
  );
}

export default function App({data = DATA_URL, mapStyle = 'mapbox://styles/mapbox/light-v9'}) {

  const [effects] = useState(() => {
    const lightingEffect = new LightingEffect({ambientLight, dirLight});
    lightingEffect.shadowColor = [0, 0, 0, 0.5];
    return [lightingEffect];
  });

  const layers = [

    // reference: https://deck.gl/docs/api-reference/layers/geojson-layer
    new GeoJsonLayer({
      id: 'nursery',
      data,
      opacity: 0.9,
      stroked: false,
      filled: true,
      extruded: true,
      wireframe: true,
      getElevation: f => f.properties.population.total * 100, // 구별 어린이집 총 수 * scale
      getFillColor: f => COLOR_SCALE(
        (f.properties.population.total*40) / (f.properties.population.newMarry*1.5) // 어린이집 여유량
      ),
      getLineColor: [255, 255, 255],
      pickable: true
    })
  ];

  // react 관련
  return (
    <DeckGL
      layers={layers}
      effects={effects}
      initialViewState={INITIAL_VIEW_STATE}
      controller={true}
      getTooltip={getTooltip}
    >
      <StaticMap
        reuseMaps
        mapStyle={mapStyle}
        preventStyleDiffing={true}
        mapboxApiAccessToken={MAPBOX_TOKEN}
      />
    </DeckGL>
  );
}

export function renderToDOM(container) {
    // 동별 어린이집
    const DATA_CSV = "mydata.txt";
    // 지도
    const DATA_JSON = 'HangJeongDong_ver20200701.geojson';
    // 동별 결혼, 이혼
    const DATA_CSV2 = "mydata2.txt";  

    // 파일을 비동기적으로 읽기
    Promise.all([
      fetch(DATA_CSV).then(response => response.text()),  // 동별 어린이집
      fetch(DATA_JSON).then(response => response.json()), // 지도
      fetch(DATA_CSV2).then(response => response.text())  // 동별 결혼, 이혼
    ])
    .then(function(values) {

      // 동별 어린이집 데이터 읽기
      const result = readString(values[0]); 

      // A helper function to parse numbers with thousand separator
      const parseIntComma = s => parseFloat(s.split(",").join(""));
      const parseDashZero = s => parseFloat(s.replaceAll("-", "0"));

      // Build population dictionary (동이름을 key로 사용)
      let dict_population = {};
      for(const row of result.data) {
          // 두 데이터의 동이름을 같게 하기 위해 인구데이터의 동이름에 포함된 "."를 모두 "·"로 치환
          let key = row[2].replaceAll(".","·"); 
          console.log(key, parseDashZero(row[3]));

          dict_population[key] = {
            total:parseDashZero(row[3]),  // 총 어린이집 수
            total_a:parseDashZero(row[4]), // 국공립
            total_b:parseDashZero(row[5]), // 사회복지법인
            total_c:parseDashZero(row[6]),  // 법인단체
            total_d:parseDashZero(row[7]), // 민간
            total_e:parseDashZero(row[8]), // 가정
            total_f:parseDashZero(row[9]), // 부모협동
            total_g:parseDashZero(row[10]), // 직장
          }
      }

      // 동별 어린이집 정보에 결혼 정보 추가
      const marry = readString(values[2]);
      for(const row of marry.data){
        let key = row[2].replaceAll(".","·"); 
        let popul = dict_population[key];
        if (popul === undefined){
          continue;
        }
        popul.newMarry = parseIntComma(row[3]);
      }

    
      // 존재하지 않는 동의 정보를 아래서 가져오게 될 경우
      // 그림 그리는 곳에서 undefined 오류 발생
      // 존재하지 않는 동의 정보는 예외 처리
      function get_dict(key){
        let ret = dict_population[key];
        if (ret === undefined){
          return {total:0, newMarry:1};
        }
        return ret;
      }


      // 지도 서울특별시 데이터만 필터링
      let filtered_features = values[1].features.filter(f => f.properties.sidonm == "서울특별시");

      // 각 동마다 인구정보를 추가
      filtered_features.forEach( function(f, idx) {
        // 각 동이름에는 "서울특별시"와 "구명"이 포함되어 있으므로 이를 제거
        this[idx].properties.population = get_dict(f.properties.adm_nm.split(" ")[2]);
      }, filtered_features);

      values[1].features = filtered_features;

      console.log(values[1]);
      render(<App data={values[1]} />, container);
    });
}
