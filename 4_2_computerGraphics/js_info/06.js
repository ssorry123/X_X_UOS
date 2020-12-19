// 1, pyramid of doom

// 2, promise vs. callbacks
let promise = new Promise(function(resolve, reject){  // 인자 둘다 함수, 고정된 파라미터
    // executor ( the producing code, "singer")
  });
  // resolve(value)
  // reject (error)
  
  // callback-based, 순서가 있는 작업 수행시, 중첩이 많이 생겨 불편함
  function loadScript1(src, callback){
    let script = document.createElement('script');  // html 로딩
    script.src = src; // src => url, 비동기적 스크립트 로딩 시작
    
    script.onload = () => callback(null, script); // 성공시
    script.onerror = () => callback(new Error(`script laod error for ${src}`)); // 실패시
  
    document.head.append(script);
  }
  // promise-based
  function loadScript2(src){
    return new Promise(function(resolve, reject){
      let script = document.createElement('script');
      script.src = src;
  
      script.onload = () => resolve(script);
      script.onerror = () => reject(new Error(`Script load error for ${src}`));
  
      document.head.append(script);
    });
  };
  
  // promise chaining, example;
  new Promise(function(resolve, reject){
    setTimeout( () => resolve(1), 1000);
  }).then(function(result){ // 성공시, then에 등록된 함수 실행
    console.log(result);  // 1
    return result*2;
  }).then(function(result){ // 성공시, then에 등록된 함수 실행
    console.log(result);  // 2
    return result*2;
  }).then(function(result){
    console.log(result);  // 3
    return result*2;
  });