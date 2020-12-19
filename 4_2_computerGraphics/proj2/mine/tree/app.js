import React from 'react';
import {render} from 'react-dom';
import {StaticMap} from 'react-map-gl';
import {AmbientLight, PointLight, LightingEffect} from '@deck.gl/core';
import {HexagonLayer} from '@deck.gl/aggregation-layers';
import DeckGL from '@deck.gl/react';
import {readString} from "react-papaparse";


// Set your mapbox token here
const MAPBOX_TOKEN = process.env.MapboxAccessToken; // eslint-disable-line

const ambientLight = new AmbientLight({
  color: [255, 255, 255],
  intensity: 1.0
});

const pointLight1 = new PointLight({
  color: [255, 255, 255],
  intensity: 0.8,
  position: [-0.144528, 49.739968, 80000]
});

const pointLight2 = new PointLight({
  color: [255, 255, 255],
  intensity: 0.8,
  position: [-3.807751, 54.104682, 8000]
});

const lightingEffect = new LightingEffect({ambientLight, pointLight1, pointLight2});

const material = {
  ambient: 0.64,
  diffuse: 0.6,
  shininess: 32,
  specularColor: [51, 51, 51]
};

const INITIAL_VIEW_STATE = {
  longitude: 126.9779,
  latitude: 37.5663,
  zoom: 10,
  minZoom: 1,
  maxZoom: 15,
  pitch: 40.5,
  bearing: -27
};

// 더 많은 세팅: https://colorbrewer2.org
// set "Number of data classes" to 6
export const colorRange = [
  [237,248,251],
  [204,236,230],
  [153,216,201],
  [102,194,164],
  [44,162,95],
  [0,109,44]
];

function getTooltip({object}) {
  if (!object) {
    return null;
  }
  const lat = object.position[1];
  const lng = object.position[0];
  const count = object.points.length;

  return `\
    latitude: ${Number.isFinite(lat) ? lat.toFixed(6) : ''}
    longitude: ${Number.isFinite(lng) ? lng.toFixed(6) : ''}
    ${count} Accidents`;
}

/* eslint-disable react/no-deprecated */
export default function App({
  data,
  mapStyle = 'mapbox://styles/mapbox/dark-v9',
  radius = 600,  
  lowerPercentile = 0,
  upperPercentile = 100,
  coverage = 1
}) {
  const layers = [
    // reference: https://deck.gl/docs/api-reference/aggregation-layers/hexagon-layer
    new HexagonLayer({
      id: 'mine',
      colorRange,
      coverage,
      data,
      elevationRange: [0, 200],
      elevationScale: data && data.length ? 100 : 0,
      extruded: true,
      getPosition: d => d,
      pickable: true,
      radius,
      upperPercentile,
      material,

      transitions: {
        elevationScale: 300
      }
    }),
    
  ];

  return (
    <DeckGL
      layers={layers}
      effects={[lightingEffect]}
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

function is_coordinates_valid(lng,lat) {
  return (Number.isFinite(lng) 
    && Number.isFinite(lat) 
    && lat >= -90 
    && lat <= 90);
}

export function renderToDOM(container) {

    // CSV version
    //fetch("locs_wifi_Seoul-UTF8.csv")
    Promise.all(
      [
        fetch("mydata3.csv").then(response => response.text()), // 보호수 및 노거수 위치 정보
        fetch("mydata4.csv").then(response => response.text()), // 공원 및 사요지수목 위치정보
      ]
    )
    //fetch("mydata3.csv")
    //.then(response => response.text())
    .then(function(values) {

      
  
      const result = readString(values[0]);
    
      const data = result.data
        // d[9] = longitude(경도), d[8] = latitude(위도)
        .map(d=>[Number(d[43]), Number(d[44])])
        // 위도&경도 유효성 검사
        .filter(d =>  
          Number.isFinite(d[0]) 
          && Number.isFinite(d[1]) 
          && d[1] >= -90 
          && d[1] <= 90);
      
      const addData = readString(values[1]);
      addData.data.forEach( function(element){
        let x = Number(element[23]);
        let y = Number(element[24]);
        if (Number.isFinite(x) && Number.isFinite(y) && y>=-90 && y<=90){
        data.push([x,y]);
        }
      }
      );
      
      console.log(data);
      
      render(<App data={data} />, container);
    });

  /*
    // JSON version
    fetch("locs_wifi_Seoul.json")
    .then(response => response.json())
    .then(function(json) {

      const data = json.DATA
        .map(d => [Number(d.instl_x), Number(d.instl_y)])
        .filter(d =>  
          Number.isFinite(d[0]) 
          && Number.isFinite(d[1]) 
          && d[1] >= -90 
          && d[1] <= 90);

      render(<App data={data} />, container);
    });
  */
}
