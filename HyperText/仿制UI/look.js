$(function(){
    function loadJson(name){
        $.ajax({
            type: "get",
            url: "data/"+name+".json",
            dataType: "json",
            success: function (data) {
                $("#count").text("总计有" + data.length + "项"+name+"！");
                var counter = 0;
                $.each(data, function(index,item){
                        counter = counter + 1;
                        $("#count").append("<br>" + counter + "." + item.名称);
                });
            }
        });
    }
    
    $("#xinfa").click(function(){
        loadJson("心法");
    });
    $("#skill").click(function(){
        loadJson("技能");
    });
    $("#shuxing").click(function(){
        loadJson("属性");
    });
});