// 모든 variables는 let으로 선언
// strict 모드에서는 var 키워드 사용 불가
// var는 사용하지 말자 (오류가 많음)
let x = "Hello!!!";
// data Types::
// Numbers, BigInt, String, Boolean, null, undefined, symbols, objects
console.log(x); // 콘솔에 출력
console.log(typeof x);
alert(x); // 메세지 박스로 출력

// 비교 연산자 ===, !==
console.log(0=="0");  // -> true, flexible type conversion
console.log(0==="0"); // -> false,