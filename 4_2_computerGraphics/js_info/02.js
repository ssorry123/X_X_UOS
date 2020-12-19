// 리턴 값이 없어도 리턴 가능
function disp(x){
    console.log(x);
    // no return
  }
  let y = disp(5);
  console.log(y); // -> undefined
  
  // 자동으로 ';' 삽입되기 때문에 조심해야 함
  function func1(x){
    return 
    x+x;
    // -> return undefined
  }
  y = disp(7645);
  console.log(y); // 7645
  
  // function Expressions
  // function이라는 변수를 만듬
  let f1 = function(x){
    return x*x;
  }
  y = f1(5);
  console.log(y); // 25
  
  // 함수와 값을 받는 함수
  let f2 = function(g, x){
    return g(x);
  }
  function double(x){
    return 2*x;
  }
  y = f2(double, 123);  // 함수와 값 전달
  console.log(y); // 246
  y = f2(function(x){return 2*x;}, 234);  // 다른 방식
  console.log(y); // 468
  y = f2(x => 2*x, 345);  // 다른 방식
  console.log(y); // 690
  
  // x,y를 g함수의 인자로 한 결과를 반환
  let f3 = function(g, x, y){
    return g(x,y);
  }
  y = f3( (x,y) => {
    return x*y;
  }, 3,5)
  console.log(y)  // 15