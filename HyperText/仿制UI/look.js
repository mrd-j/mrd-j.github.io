$(function(){
    $("button").click(function(){
        var id = $(this).attr("class");
        $.ajax({
            type: "get",
            url: "data/"+id+".json",
            dataType: "json",
            success: function (data) {
                $("#count").text("总计有" + data.length + "项"+id+"！");
                var counter = 0;
                $.each(data, function(index,item){
                    if ($.isArray(item)) {
                        $.each(item,function(key,value){
                            $("#count").append("<br>"+value.名称);
                        });
                    }
                    else{
                        counter = counter + 1;
                        $("#count").append("<br>" + counter + "." + item.名称);
                    }
                });
            }
        });
    });
});