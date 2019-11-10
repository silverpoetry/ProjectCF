# ProjectCF
# 导数应用

- # 微分中值定理
  - 费马定理
  - 罗尔定理
  - 柯西中值定理
  - 拉格朗日中值定理

 <div id="domover">
    <div id="divcircle" class="divcircle" ></div>
    <div class="divback"> </div>
    <div id="divCircleContent">Z</div>
    <div id="divzhezhao" ></div>
</div>
<style>
#domover {
 width: 100px;
    height: 100px;
    position:absolute;
    top:calc(50%-50px);
    left:calc(50%-50px);   
     z-index: 9999;
}
.divcircle {
    border-radius: 500px;  
    background-color: aquamarine;
    position: absolute;
    top:0px;
    left:0px;
    width:100%;
    height:100%;
    -moz-box-shadow: 0px 0px 20px 0px rgba(0,0,0,0.2), 0px 0px 20px 0px rgba(0,0,0,0.19);
    -webkit-box-shadow: 0px 0px 20px 0px rgba(0,0,0,0.2), 0px 0px 20px 0px rgba(0,0,0,0.19);
    box-shadow: 0px 0px 20px 0px rgba(0,0,0,0.2), 0px 0px 20px 0px rgba(0,0,0,0.19);
    /*以下为了文字居中*/
}
#divCircleContent {
    width: 50%;
    height: 50%;
    overflow: auto;
    margin: auto;
    position: absolute;
    top: 0;
    left: 0;
    bottom: 0;
    right: 0;
    overflow: hidden;
    color: palegoldenrod;
    text-align: center;
    font-size :60px;
    line-height :50px;
}
.divback {
    border-radius: 500px;
    width: 100%;
    height: 100%;
    background-color: aquamarine;
    animation-name: echo;
    animation-duration: 2000ms;
    animation-timing-function: cubic-bezier(0, 0, 0, 1.74);
    animation-delay: 0ms;
    animation-iteration-count: infinite;
    animation-play-state: running;
    -webkit-animation-name: echo;
    -webkit-animation-duration: 2000ms;
    -webkit-animation-timing-function: cubic-bezier(0, 0, 0, 1.74);
    -webkit-animation-delay: 0ms;
    -webkit-animation-iteration-count: infinite;
    -webkit-animation-play-state: running;
    position: relative;
}
@keyframes echo {
    0% {
        /*脉冲动画*/
        opacity: 0.2;
        transform: scale(1);
    }
    100% {
        opacity: 0;
        transform: scale(1.6);
    }
}
@-webkit-keyframes echo {
    0% {
        /*脉冲动画*/
        opacity: 0.2;
        transform: scale(1);
        -webkit-transform: scale(1);
    }
  100% {
        opacity: 0;
        -webkit-transform: scale(1.6);
    }
}
</style>
