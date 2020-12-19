// 1, f는 비동기적으로 실행, 끝나면 바로 종료됨, 기다리지 않음
async function f(){
    return 1;
  }
  f().then(console.log);  // 1
  
  // 2, await, only in async function
  async function f1(){
    let promise = new Promise((resolve, reject) =>{
      setTimeout( () => resolve(`done!`), 1000);
    });
    let ret = await promise;  // resolve가 끝나길 기다림
    console.log(ret);
  }
  f1();
  
  // 3
  async function f2(){
    try{
      let response = await fetch('http://no-such_url');
    }catch(err){
      alert(err);
    }
  }
  f2();