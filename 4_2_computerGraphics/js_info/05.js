// 1
let arr = [3,5,1];
console.log(Math.max(...arr)) // 5
let arrCopy = [...arr]; // shallow copy

// 2,  fuction 내부의 값들이 보존됨
function makeCounter(){
  let count = 0;
  // 내부에서 만들어진 함수는 내부의 값을 통제할 수 있음
  return function(){  // noname function
    return count++;
  }
}
let counter = makeCounter();
console.log(counter()); // 0
console.log(counter()); // 1
console.log(counter()); // 2

// 이름 없는 함수를 만들고, 실행시킴
let counter2 = ( function(){
  let count = 0;
  return function(){
    return count++;
  };
}
)();
console.log(counter2());  // 0
console.log(counter2());  // 1
console.log(counter2());  // 2

// 3, function == object
function sum(a,b){
  return a+b;
}
sum.my_name = "sum function";
console.log(sum.name);  // sum
console.log(sum.my_name); // sum function

// 4
function sayHi(){
  alert('Hello');
}
// setTimeout(sayHi, 1000);  // after 1s, 'Hello'

// 잘 사용하지 않음
// let timerId = setInterval( () => alert(`tick`), 2000);  // 2초마다 알림
// setTimeout( () => { clearInterval(timerId); alert('stop');}, 5000); // 5초 후, 중지시킴

// 5, async, end with ... 이 먼저 출력된다
function f(){
  console.log(`in f`);
}
// 0초 후에 f를 실행해라, 하지만 늦게 실행됨;;
setTimeout(f, 0); // (second), in f 
let x = 0;
for (let i=0; i<1000; i++){ // just user delay
  x = x+i;
}
console.log(`end with x = ${x}`); // (first), end with x = 499500

// 6
let group = {
  title : `our Group`,
  students : [`A`, `B`, `C`],
  
  showList(){
    this.students.forEach(
      student => console.log(this.title + ` : ` + student)
    );
  }
};
group.showList();

function square_f(a){
  return a*a;
}
let square_arrow = (a) => a*a;
console.log([1,2,3,4].map(square_f)); // [1, 4, 9, 16]
console.log([1,2,3,4].map(a=> a*a)); // [1, 4, 9, 16]

// 7
class User{
  constructor(name){
    this.name = name;
  }

  sayHi(){
    console.log(this.name);
  }
}
let user = new User(`John`);
user.sayHi(); // John