# 데이터
mydata.txt : 서울특별시 보육시설(어린이집) 현황(종료예정)
-> 동별 어린이집 총 수에 따라 높이 설정

mydata2.txt : 서울시 혼인이혼(동별) 통계
-> 동별 신혼 수 사용



# 시각화
하나의 어린이집 평균 정원 40으로 가정
신혼 부부가 평균 1.5명 출산한다고 가정

어린이집 여유량 = (총어린이집수*40) / (신혼부부수*1.5)
-> 색깔로 표현
여유량이 높을 수록 색깔이 진한 빨간색으로 표현됩니다
여유량이 낮을 수록 색깔이 연하게 표현됩니다.

진한 빨간색인 지역:
아기에 비해 어린이집이 많아서
아기를 쉽게 어린이집에 맞길 수 있는 지역입니다.

연한 빨간색인 지역:
아기에 비해 어린이집이 적어서
어린이집이 더 있으면 좋을 것 같은 지역입니다.