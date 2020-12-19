// 3
// key value object
// let user ={ // or
const user = {
  name : "John",
  age : 30,
  address1 : "add1",
  address2 : "add2"
};
console.log(user.name); // John
console.log(user["name"]); // John
console.log(user["address"+1])  // add1
delete user.name; // 동적 삭제
console.log(user.name); // undefined

const v = 5;
// v = 3;  // error,

// const지만 안의 내용은 수정 가능
// user는 reference, reference값만 바꿀 수 없음
user.age = 12;
console.log(user.age) // 12

// 4
// 모양이 같은 object를 여러개 만드는 함수
function makeUser(name, age){
  return{
    name: name,
    age: age,
    // ... other properties
  };
}
let u = makeUser("Johng", 30);
console.log(u.name) // Johng

let admin1 = u;  // object copying, references
u.name = "ABC";
console.log(admin1.name);  // ABC

// js 레벨에서 깊은 복사는 지원하지 않음
let admin2 = Object.assign({}, u);  // shallow copying(얕은 복사)
u.name = "DEF";
console.log(admin2.name); // ABC

// 5
let user2 = {
  name : "John",
  sayHi : function(){
    alert("Hello!");
  }
}
user2.sayHi();  // Hello!

// 6
function User3(name){
  this.name = name;
  this.isAdmin = false;
}
let user3 = new User3("Jack"); // make new object, this === user3
console.log(user3.name); // Jack
console.log(user3.isAdmin); // false

let user4 = User3("Jack");  // no new, this === window object
// console.log(user4.name); // error
// console.log(user4.isAdmin); // error
console.log(window.name); // Jack
console.log(window.isAdmin);  // false