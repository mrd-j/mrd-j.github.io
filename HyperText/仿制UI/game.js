$(function(){
    $("#bt").click(function () {
        $.ajax({
            type: "get",
            url: "data/心法.json",
            dataType: "json",
            success: function (data) {
                $(".content p").text("内容区");
                $("#rumen").text(data[0].心法名称);
                $("#jinjie").text(data[1].心法名称);
                $.gamedata = data;
            }
        });
    });
    $("#rumen").click(function () {
        $(".content p").text($.gamedata[0].skill[0].技能名称);
        $(".content p").append("<br>"+$.gamedata[0].skill[1].技能名称);
        $(".content p").append("<br>"+$.gamedata[0].skill[2].技能名称);
        $(".content p").append("<br>"+$.gamedata[0].skill[3].技能名称);
    });
    $("#jinjie").click(function () {
        $(".content p").text("等级："+$.gamedata[0].心法等级);
    });
    });