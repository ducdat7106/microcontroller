// khoi tao cac thong so
let btn1 = document.querySelector('#btn1');
let img = document.querySelector('img');
let btn2 = document.querySelector('#btn2');

// functions nut bam
btn1.addEventListener('click', ()=>{
    img.src = 'img/fan_running.png'; 
})

btn2.addEventListener('click', ()=>{
    img.src = 'img/fan_off.png';
})