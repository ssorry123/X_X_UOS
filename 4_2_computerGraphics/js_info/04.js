// 1
// primitive -> string, number, BigInt, boolean, symbol, null and undefined
// object -> functions, or ....,, heavy than primitive
// object rappers : ex) String, Number, Booelan, symbol
let str = "Hello";
console.log(str.toUpperCase()); // HELLO

// 2
// Numbers
// double floating, or, BigInt
// isNAan, isFinite
// parseInt, parseFloat
// Math object
console.log(Math.PI);

// 3
// 권장되는 Strings 표현법, backticks (``)
function sum(a,b){return a+b;}
str = `1 + 2 = ${sum(1,2)}.`; // 유용
console.log(str); // 1 + 2 = 3.
str = "1 + 2 = " + sum(1,2) + ".";  // 지저분, 성능 별로
console.log(str); // 1 + 2 = 3.
let list = `abc:
*a
*b
*c
`;
console.log(list) // 줄바꿈 지원

str = `appleBanana`;
console.log(str.slice(0,5)); // apple

// 4
// Arrays, object
let fruits = [`Apple`, 231, true];
for (let fruit of fruits){
  console.log(fruit); // Apple, 231, true
}
fruits.splice(1,1);
console.log(fruits); // ["Apple", true]

let arr = [`t`, `e`, `s`, `t`]
console.log(arr.slice(1,3)); // e, s
console.log(arr.slice(-2)); // s, t

// 5
let users = [
  {id: 1, name: "A"},
  {id: 2, name: "B"},
  {id: 3, name: "C"}
]
let someUsers = users.filter(item => item.id < 3);
console.log(someUsers.length); // 2

let user = {id:1, name :"John"};
console.log(Object.keys(user)); // [ "id", "name" ]
console.log(Object.values(user)); // [1, "John"]
console.log(Object.entries(user));
for (let k in user){
  console.log(k)  // id, name
}
for (let k of Object.keys(user)){
  console.log(k)  // id, name
}

// 6
arr = ["Ilya", "Kantor"];
let [firstName, surname, yy] = arr;
console.log(firstName); // Ilya
console.log(surname); // Kantor
console.log(yy);  // undefined

[firstName, surname] = `james parker`.split(' ');
console.log(firstName); // james
console.log(surname); // parker

// 7, rest parameter
let [n1, n2, ...rest] = [1, 2, 3, 4, 5, 6, 7];
console.log(rest) // [3,4,5,6,7]

// 8, 
let options = {
  title: 'Menu',
  width : 100,
  height : 200
};
let {width, height, title} = options; // key값에 맞게 들어감
console.log(title); // Menu
console.log(width); // 100
console.log(height); // 200

function display_name({first = `lala`, last}){  // default `lala`
  console.log(`${first} ${last}`);
}
display_name({first:'SEOWON', last:`PARK`});  // SEOWON PARK

// 9, object to json
let s = {
  name: `Jhon`,
  age: 30,
  isAdmin:false,
  courses:[`html`, `css`, `js`],
  wife: null
};
let json = JSON.stringify(s);
console.log(typeof json); // string
alert(json);  // {"name":"Jhon","age":30,"isAdmin":false,"courses":["html","css","js"],"wife":null}

// 10, json to object
let numbers = `[0,1,2,3]`;
numbers = JSON.parse(numbers);
console.log(numbers[1]); // 1