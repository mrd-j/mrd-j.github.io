function txtAdd() {
  document.getElementById("txtCreat").value = "日期：" + Date();
};

var size=20;

function fontSizeUp(){
size++;
document.getElementById("xu").style.fontSize=size+"px";
};

function fontSizeDown(){
size--;
document.getElementById("xu").style.fontSize=size+"px";
}
