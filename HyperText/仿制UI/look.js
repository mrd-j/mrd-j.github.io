$(function(){
    function loadJson(name){
        $.ajax({
            type: "get",
            url: "data/"+name+".json",
            dataType: "json",
            success: function (data) {
                $.gamedata = data;
                $("#xiangqing").html("");
                $("#count").text("总计有" + data.length + "项"+name+"！");
                var counter = 0;
                $.each(data, function(index,item){
                        counter = counter + 1;
                        $("#count").append("<br>" + counter + "." + "<a id='"+item.名称+"' href='#'>"+item.名称+"</a>");
                });
            }
        });
    }
    
    $("#xinfa").click(function(){
        $.typ = "心法";
        loadJson("心法");
    });
    $("#skill").click(function(){
        $.typ = "技能";
        loadJson("技能");
    });
    $("#shuxing").click(function(){
        loadJson("属性");
    });
    $("body").on("click","a",function(){
        var name = $(this).attr("id");
        //alert($.typ);
        $.each($.gamedata, function(index,item){
            if (item.名称===name) {
                $("#xiangqing").html("");
                $.each(item, function(key,value){
                    if ($.isPlainObject(value)){
                        $("#xiangqing").append("<br>" + key + ":");
                        $.each(value, function(k,v){
                            $("#xiangqing").append("【" + k + v + "】");
                        });
                    }
                    else{
                        $("#xiangqing").append("<br>" + key + ":" + value);
                    }
                    
                });
            }
        });
        //$("#xiangqing").append
        //loadJson("属性");
    });
});