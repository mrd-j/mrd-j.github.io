// This program is a part of NITAN MudLIB

mapping region_names = ([
        "baituo"   : "西域白驼山",
        "beijing"  : "北京城",
        "changan"  : "长安城",
        "city"     : "扬州城",
        "chengdu"  : "成都城",
        "dali"     : "云南大理城",
        "death"    : "鬼门关",
        "emei"     : "四川峨嵋",
        "foshan"   : "广东佛山",
        "fuzhou"   : "福建福州",
        "gaibang"  : "丐帮所在地",
        "guanwai"  : "关外境内",
        "guiyun"   : "归云庄",
        "gumu"     : "古墓派境内",
        "hangzhou" : "杭州城",
        "heimuya"  : "黑木崖境内",
        "hengshan" : "恒山境内",
        "hengyang"  : "衡山境内",
        "huanggon" : "皇宫",
        "huanghe"  : "黄河边",
        "huashan"  : "华山境内",
        "jinshe"   : "华山金蛇洞",
        "jingzhou" : "荆州境内",
        "lingjiu"  : "灵鹫宫境内",
        "lingzhou" : "灵州城",
        "luoyang"  : "洛阳境内",
        "lanzhou"  : "兰州境内",
        "kaifeng"  : "开封境内",
        "kunming"  : "昆明境内",
        "meizhuang": "梅庄",
        "mingjiao" : "明教境内",
        "pk"       : "屠人场",
        "qingcheng": "青城山境内",
        "quanzhen" : "全真派境内",
        "shaolin"  : "少林寺境内",
        "shenlong" : "神龙岛境内",
        "songshan" : "嵩山境内",
        "suzhou"   : "苏州城",
        "taishan"  : "泰山境内",
        "taohua"   : "桃花岛境内",
        "tianlongsi": "天龙寺境内",
        "tulong"   : "万安寺或者王盘山岛",
        "village"  : "华山村",
        "wanjiegu" : "万劫谷",
        "wizard"   : "仙界",
        "wudang"   : "武当山境内",
        "xiakedao" : "侠客岛境内",
        "xiangyang": "襄阳城",
        "xiaoyao"  : "逍遥派境内",
        "xingxiu"  : "星宿派境内",
        "xuedao"   : "血刀门境内",
        "xueshan"  : "雪山寺",
        "yangziwu" : "燕子钨",
        "zhongzhou": "中州境内",
        "sdxl"     : "剑冢",
        "tangmen"  : "四川唐门境内",
        "wansong"  : "万松山庄",
        //新增：
        "kunlun"   : "昆仑山境内",
        "yanziwu"  : "燕子坞",
        "motianya" : "摩天崖",
        "register" : "注册账号",
]);

mapping place = ([
        "city"     : ({
                "扬州郊外", ({
                        "/d/city/jiaowai1",
                        "/d/city/jiaowai2",
                        "/d/city/jiaowai3",
                        "/d/city/jiaowai4",
                        "/d/city/jiaowai5",
                        "/d/city/jiaowai6",
                        "/d/city/jiaowai7",
                        "/d/city/jiaowai8",
                        "/d/city/jiaowai9",
                        "/d/city/jiaowai10",
                        "/d/city/jiaowai11",
                        "/d/city/jiaowai12",
                        "/d/city/jiaowai13"
                }),}),
        "guiyun"   : ({
                "太湖一带", ({
                        "/d/guiyun/shulin1",
                        "/d/guiyun/shulin2",
                        "/d/guiyun/shulin3",
                        "/d/guiyun/shulin4",
                        "/d/guiyun/shulin5",
                        "/d/guiyun/shanlu1",
                        "/d/guiyun/shanlu2",
                        "/d/guiyun/tiandi"
                }),}),
        "huanghe"   : ({
                "黄河一带", ({
                        "/d/huanghe/caodi1",
                        "/d/huanghe/caodi2",
                        "/d/huanghe/shulin1",
                        "/d/huanghe/shulin2",
                        "/d/huanghe/shulin3",
                        "/d/huanghe/shulin4",
                        "/d/huanghe/shulin5",
                        "/d/huanghe/shulin6",
                        "/d/huanghe/tiandi1",
                        "/d/huanghe/tiandi2",
                        "/d/huanghe/tiandi3",
                        "/d/huanghe/tiandi4",
                        "/d/huanghe/huanghe1",
                        "/d/huanghe/huanghe2",
                        "/d/huanghe/huanghe3",
                        "/d/huanghe/huanghe4",
                        "/d/huanghe/huanghe5",
                        "/d/huanghe/huanghe6",
                        "/d/huanghe/huanghe7",
                        "/d/huanghe/huanghe8",
                        "/d/huanghe/bingcao",
                        "/d/huanghe/dacaigou",
                        "/d/huanghe/guchangcheng",
                        "/d/huanghe/gulang",
                        "/d/huanghe/hongshanxia",
                        "/d/huanghe/hetao",
                        "/d/huanghe/huanghe_1",
                        "/d/huanghe/huanghe_2",
                        "/d/huanghe/huanghe_3",
                        "/d/huanghe/huangtu",
                        "/d/huanghe/liupanshan",
                        "/d/huanghe/qingcheng",
                        "/d/huanghe/shimen",
                        "/d/huanghe/shixiazi",
                        "/d/huanghe/tumenzi",
                        "/d/huanghe/weifen",
                        "/d/huanghe/wufosi",
                        "/d/huanghe/wuqiao",
                        "/d/huanghe/xiaojiaqiao",
                        "/d/huanghe/yinpanshui"
                }),}),
        "guanwai"   : ({
                "长白山上", ({
                        "/d/guanwai/milin1",
                        "/d/guanwai/milin2",
                        "/d/guanwai/milin3",
                        "/d/guanwai/heifengkou",
                        "/d/guanwai/xiaotianchi",
                        "/d/guanwai/pubu",
                        "/d/guanwai/damen",
                        "/d/guanwai/longmen",
                        "/d/guanwai/tianhuo",
                        "/d/guanwai/huagai",
                        "/d/guanwai/tianchi1",
                        "/d/guanwai/tianchi2",
                        "/d/guanwai/baiyun",
                        "/d/guanwai/luming",
                        "/d/guanwai/famu",
                        "/d/guanwai/yuzhu",
                        "/d/guanwai/tiyun"
                }),}),
        "dali"      : ({
                "大理郊外", ({
                        "/d/dali/atoubu",
                        "/d/dali/badidian",
                        "/d/dali/banshan",
                        "/d/dali/bijishan",
                        "/d/dali/biluoshan",
                        "/d/dali/biluoxueshan",
                        "/d/dali/buxiongbu",
                        "/d/dali/cangshan",
                        "/d/dali/cangshanlu1",
                        "/d/dali/cangshanzhong",
                        "/d/dali/caopo",
                        "/d/dali/chahuashan1",
                        "/d/dali/chahuashan2",
                        "/d/dali/chahuashan3",
                        "/d/dali/chahuashan4",
                        "/d/dali/chahuashan5",
                        "/d/dali/chahuashan6",
                        "/d/dali/changhu",
                        "/d/dali/dadieshui",
                        "/d/dali/daduhe",
                        "/d/dali/dalinorth",
                        "/d/dali/dasenlin",
                        "/d/dali/dehuabei",
                        "/d/dali/dianchi",
                        "/d/dali/ershuiqiao",
                        "/d/dali/feilihu",
                        "/d/dali/feilihueast",
                        "/d/dali/feilihusouth",
                        "/d/dali/gaolishan1",
                        "/d/dali/gaolishan2",
                        "/d/dali/gelucheng",
                        "/d/dali/gudao",
                        "/d/dali/hebian",
                        "/d/dali/heilongling",
                        "/d/dali/heisenlin",
                        "/d/dali/heshang",
                        "/d/dali/hole",
                        "/d/dali/hongsheng",
                        "/d/dali/hongsheng",
                        "/d/dali/hongsheng1",
                        "/d/dali/hongsheng2",
                        "/d/dali/hongsheng3",
                        "/d/dali/hongsheng4",
                        "/d/dali/hudiequan",
                        "/d/dali/jinzhihe",
                        "/d/dali/luojiadian",
                        "/d/dali/lushuieast",
                        "/d/dali/luyuxi",
                        "/d/dali/milin",
                        "/d/dali/minadian",
                        "/d/dali/nongtian1",
                        "/d/dali/nongtian2",
                        "/d/dali/nongtian3",
                        "/d/dali/nongtian4",
                        "/d/dali/nongtian5",
                        "/d/dali/qingzhulin",
                        "/d/dali/road1",
                        "/d/dali/road2",
                        "/d/dali/road3",
                        "/d/dali/road4",
                        "/d/dali/road5",
                        "/d/dali/sanglin",
                        "/d/dali/shanjian",
                        "/d/dali/shanlin",
                        "/d/dali/shanlu1",
                        "/d/dali/shanlu2",
                        "/d/dali/shanlu3",
                        "/d/dali/shanlu4",
                        "/d/dali/shanlu5",
                        "/d/dali/shanlu6",
                        "/d/dali/shanlu7",
                        "/d/dali/shanlu8",
                        "/d/dali/shilin",
                        "/d/dali/shilin1",
                        "/d/dali/shilin2",
                        "/d/dali/shuangheqiao",
                        "/d/dali/shuitian",
                        "/d/dali/shulinwai",
                        "/d/dali/tianweijing",
                        "/d/dali/titian1",
                        "/d/dali/wuding",
                        "/d/dali/wumeng",
                        "/d/dali/xingyunhu",
                        "/d/dali/yanan1",
                        "/d/dali/yanan2",
                        "/d/dali/yanchi1",
                        "/d/dali/yanchi2",
                        "/d/dali/yanchi3",
                        "/d/dali/yixibu",
                        "/d/dali/yulin",
                        "/d/dali/yuxiashan",
                        "/d/dali/zhulin",
                        "/d/dali/zhulin2"
                }),}),
        "foshan"   : ({
                "佛山一带", ({
                        "/d/foshan/nanling",
                        "/d/foshan/road1",
                        "/d/foshan/road2",
                        "/d/foshan/road3",
                        "/d/foshan/road4",
                        "/d/foshan/road5",
                        "/d/foshan/road6",
                        "/d/foshan/road7",
                        "/d/foshan/road8",
                        "/d/foshan/road9",
                        "/d/foshan/road10",
                        "/d/foshan/road11",
                        "/d/foshan/road12",
                        "/d/foshan/road13",
                        "/d/foshan/road14"
                }),}),
        "fuzhou"   : ({
                "福州一带", ({ "/d/fuzhou/fzroad1",
                        "/d/fuzhou/fzroad2",
                        "/d/fuzhou/fzroad3",
                        "/d/fuzhou/fzroad4",
                        "/d/fuzhou/fzroad5",
                        "/d/fuzhou/fzroad6",
                        "/d/fuzhou/fzroad7",
                        "/d/fuzhou/fzroad8",
                        "/d/fuzhou/fzroad9",
                        "/d/fuzhou/fzroad10",
                        "/d/fuzhou/fzroad11",
                        "/d/fuzhou/gushan",
                        "/d/fuzhou/haigang",
                        "/d/fuzhou/pingshan",
                        "/d/fuzhou/puxian",
                        "/d/fuzhou/shulin",
                        "/d/fuzhou/wushan",
                        "/d/fuzhou/wuyishan1",
                        "/d/fuzhou/wuyishan2",
                        "/d/fuzhou/wuyishan3",
                        "/d/fuzhou/wuyishan4",
                        "/d/fuzhou/wuyishan5",
                        "/d/fuzhou/wuyishan6",
                        "/d/fuzhou/wuyishan7",
                        "/d/fuzhou/yushan"
                }),}),
        "hengshan"  : ({
                "恒山一带", ({ "/d/hengshan/cuiping1",
                        "/d/hengshan/cuiping2",
                        "/d/hengshan/cuipinggu1",
                        "/d/hengshan/cuipinggu2",
                        "/d/hengshan/daziling",
                        "/d/hengshan/guolaoling",
                        "/d/hengshan/hufengkou",
                        "/d/hengshan/jinlongxia",
                        "/d/hengshan/shandao1",
                        "/d/hengshan/shandao2",
                        "/d/hengshan/tongyuangu",
                        "/d/hengshan/xuangengsong",
                        "/d/hengshan/yunge",
                        "/d/hengshan/yuyang",
                        "/d/hengshan/zhandao",
                        "/d/hengshan/zhanqiao"
                }),}),
        "hengyang"   : ({
                "衡山一带", ({ "/d/hengyang/banshan",
                        "/d/hengyang/chidifeng",
                        "/d/hengyang/denggaotai",
                        "/d/hengyang/heishatan",
                        "/d/hengyang/hsroad1",
                        "/d/hengyang/hsroad2",
                        "/d/hengyang/hsroad3",
                        "/d/hengyang/hsroad4",
                        "/d/hengyang/hsroad5",
                        "/d/hengyang/hsroad6",
                        "/d/hengyang/hsroad7",
                        "/d/hengyang/hsroad8",
                        "/d/hengyang/hsroad9",
                        "/d/hengyang/lingxingmen",
                        "/d/hengyang/liuyunping",
                        "/d/hengyang/mojingtai",
                        "/d/hengyang/nantian",
                        "/d/hengyang/shanjian",
                        "/d/hengyang/shanlu1",
                        "/d/hengyang/shanlu2",
                        "/d/hengyang/shanlu3",
                        "/d/hengyang/shanlu4",
                        "/d/hengyang/shanlu5",
                        "/d/hengyang/shanlu6",
                        "/d/hengyang/shanlu7",
                        "/d/hengyang/shanlu8",
                        "/d/hengyang/shanlu9",
                        "/d/hengyang/shanlu10",
                        "/d/hengyang/shanlu11",
                        "/d/hengyang/shanlu12",
                        "/d/hengyang/shanlu13",
                        "/d/hengyang/shanlu14",
                        "/d/hengyang/shiziyan",
                        "/d/hengyang/shuiliandong",
                        "/d/hengyang/tianzhu",
                        "/d/hengyang/yubeiting",
                        "/d/hengyang/zhengchuan",
                        "/d/hengyang/zhongting",
                        "/d/hengyang/zhurongfeng"
                }),}),
        "huashan" :  ({
                "华山一带", ({ "/d/huashan/baichi",
                        "/d/huashan/canglong",
                        "/d/huashan/chaopath1",
                        "/d/huashan/chaopath2",
                        "/d/huashan/chengxiang",
                        "/d/huashan/huixinshi",
                        "/d/huashan/husun",
                        "/d/huashan/jiashan",
                        "/d/huashan/jinsuo",
                        "/d/huashan/jzroad1",
                        "/d/huashan/jzroad2",
                        "/d/huashan/jzroad3",
                        "/d/huashan/jzroad4",
                        "/d/huashan/jzroad5",
                        "/d/huashan/laojun",
                        "/d/huashan/lianhua",
                        "/d/huashan/lianpath1",
                        "/d/huashan/lianpath2",
                        "/d/huashan/path1",
                        "/d/huashan/pingdi",
                        "/d/huashan/pingxinshi",
                        "/d/huashan/qianchi",
                        "/d/huashan/qingke",
                        "/d/huashan/shaluo",
                        "/d/huashan/shangtianti",
                        "/d/huashan/shangu",
                        "/d/huashan/shanhongpb",
                        "/d/huashan/sheshen",
                        "/d/huashan/siguoya",
                        "/d/huashan/songlin1",
                        "/d/huashan/songlin2",
                        "/d/huashan/songlin3",
                        "/d/huashan/songlin4",
                        "/d/huashan/xiaolu1",
                        "/d/huashan/xiaolu2",
                        "/d/huashan/xuanya",
                        "/d/huashan/yunmen",
                        "/d/huashan/yuntai",
                        "/d/huashan/yunu",
                        "/d/huashan/yunupath1",
                        "/d/huashan/yunupath2",
                        "/d/huashan/zhandao",
                        "/d/huashan/ziqitai"
                }),}),
        "qingcheng" :  ({
                "青城山上", ({ "/d/qingcheng/gulongqiao",
                        "/d/qingcheng/maguchi",
                        "/d/qingcheng/path1",
                        "/d/qingcheng/path2",
                        "/d/qingcheng/qcroad1",
                        "/d/qingcheng/qcroad2",
                        "/d/qingcheng/qcroad3",
                        "/d/qingcheng/sandaoshi",
                        "/d/qingcheng/sanwanjiudao",
                        "/d/qingcheng/tianran",
                        "/d/qingcheng/tianshidong",
                        "/d/qingcheng/xiaoqiao",
                        "/d/qingcheng/yinxing",
                        "/d/qingcheng/yuanyangjing",
                        "/d/qingcheng/zhuhezhuang",
                        "/d/qingcheng/zushidian"
                }),}),
        "lingzhou" : ({
                "灵州一带", ({ "/d/lingzhou/chiling",
                        "/d/lingzhou/dalu",
                        "/d/lingzhou/deling",
                        "/d/lingzhou/gongling",
                        "/d/lingzhou/huangyangtan",
                        "/d/lingzhou/kongdi",
                        "/d/lingzhou/luorilin1",
                        "/d/lingzhou/luorilin2",
                        "/d/lingzhou/mingshazhou",
                        "/d/lingzhou/qingtongxia",
                        "/d/lingzhou/qingxinquan",
                        "/d/lingzhou/tulu",
                        "/d/lingzhou/wangling",
                        "/d/lingzhou/xiaoba",
                        "/d/lingzhou/xiaolu1",
                        "/d/lingzhou/xiaolu2",
                        "/d/lingzhou/xiaolu3",
                        "/d/lingzhou/xuanhebao"
                }),}),
        "quanzhen"   : ({
                "终南山一带", ({ "/d/quanzhen/baishulin1",
                        "/d/quanzhen/baishulin2",
                        "/d/quanzhen/baishulin3",
                        "/d/quanzhen/baishulin4",
                        "/d/quanzhen/banshanting",
                        "/d/quanzhen/cuipingfeng",
                        "/d/quanzhen/cuipinggu",
                        "/d/quanzhen/cundaota1",
                        "/d/quanzhen/cundaota2",
                        "/d/quanzhen/cundaota3",
                        "/d/quanzhen/cundaota4",
                        "/d/quanzhen/fangzhenqiao",
                        "/d/quanzhen/guanritai",
                        "/d/quanzhen/shanjiao",
                        "/d/quanzhen/shanlu1",
                        "/d/quanzhen/shanlu2",
                        "/d/quanzhen/shanlu3",
                        "/d/quanzhen/shanlu4",
                        "/d/quanzhen/shijie1",
                        "/d/quanzhen/shijie2",
                        "/d/quanzhen/shijie3",
                        "/d/quanzhen/shijie4",
                        "/d/quanzhen/shijie5",
                        "/d/quanzhen/shijie6",
                        "/d/quanzhen/shijie7",
                        "/d/quanzhen/shijie8",
                        "/d/quanzhen/shijie9",
                        "/d/quanzhen/xiaomiao",
                }),}),
        "gumu"   : ({
                "终南山一带", ({
                        "/d/gumu/baimatang",
                        "/d/gumu/baoziyan",
                        "/d/gumu/caodi",
                        "/d/gumu/caodi2",
                        "/d/gumu/foyezhang",
                        "/d/gumu/hanshuitan",
                        "/d/gumu/heifengdong",
                        "/d/gumu/huangshalin",
                        "/d/gumu/jinliange",
                        "/d/gumu/juyan",
                        "/d/gumu/kongdi",
                        "/d/gumu/riyueyan",
                        "/d/gumu/shandao1",
                        "/d/gumu/shandao2",
                        "/d/gumu/shandao3",
                        "/d/gumu/shandong",
                        "/d/gumu/shanlu1",
                        "/d/gumu/shanlu2",
                        "/d/gumu/shanlu3",
                        "/d/gumu/shanlu4",
                        "/d/gumu/shanlu5",
                        "/d/gumu/shanlu6",
                        "/d/gumu/shanlu7",
                        "/d/gumu/shanlu8",
                        "/d/gumu/shanlu9",
                        "/d/gumu/shanlu10",
                        "/d/gumu/shanlu11",
                        "/d/gumu/shanlu12",
                        "/d/gumu/shanlu13",
                        "/d/gumu/shanlu14",
                        "/d/gumu/shanlu15",
                        "/d/gumu/shanlu16",
                        "/d/gumu/shenheyuan",
                        "/d/gumu/shulin0",
                        "/d/gumu/shulin1",
                        "/d/gumu/shulin2",
                        "/d/gumu/shulin3",
                        "/d/gumu/shulin4",
                        "/d/gumu/shulin5",
                        "/d/gumu/shulin6",
                        "/d/gumu/shulin7",
                        "/d/gumu/shulin8",
                        "/d/gumu/shulin9",
                        "/d/gumu/shulin10",
                        "/d/gumu/shulin11",
                        "/d/gumu/shulin12",
                        "/d/gumu/taiyi1",
                        "/d/gumu/xiaohebian",
                        "/d/gumu/zhufeng"
                }),}),
        "songshan"  : ({
                "嵩山一带", ({ "/d/songshan/chaotian",
                        "/d/songshan/chongsheng",
                        "/d/songshan/fengchantai",
                        "/d/songshan/luyanpubu",
                        "/d/songshan/qimuque",
                        "/d/songshan/qimushi",
                        "/d/songshan/shandao1",
                        "/d/songshan/shandao2",
                        "/d/songshan/shandao3",
                        "/d/songshan/shandao4",
                        "/d/songshan/shandao5",
                        "/d/songshan/shandao6",
                        "/d/songshan/taishique",
                        "/d/songshan/tianzhongge"
                }),}),
        "taishan" :  ({
                "泰山一带", ({ "/d/taishan/baihe",
                        "/d/taishan/baozang",
                        "/d/taishan/beitian",
                        "/d/taishan/daizong",
                        "/d/taishan/dongtian",
                        "/d/taishan/doumo",
                        "/d/taishan/huima",
                        "/d/taishan/lianhua",
                        "/d/taishan/longmen",
                        "/d/taishan/nantian",
                        "/d/taishan/shengxian",
                        "/d/taishan/shijin",
                        "/d/taishan/shixin",
                        "/d/taishan/taishanjiao",
                        "/d/taishan/tanhai",
                        "/d/taishan/weipin",
                        "/d/taishan/wudafu",
                        "/d/taishan/xitian",
                        "/d/taishan/yidao3",
                        "/d/taishan/yitian",
                        "/d/taishan/yueguan",
                        "/d/taishan/yuhuang",
                        "/d/taishan/zhangren"
                }),}),
        "xueshan" : ({
                "雪山脚下", ({ "/d/xueshan/caoyuan",
                        "/d/xueshan/caoyuan1",
                        "/d/xueshan/hubian1",
                        "/d/xueshan/hubian2",
                        "/d/xueshan/hubian3",
                        "/d/xueshan/hubian4",
                        "/d/xueshan/shanjiao",
                        "/d/xueshan/shenghu",
                        "/d/xueshan/tulu1",
                        "/d/xueshan/tulu2",
                        "/d/xueshan/tulu3"
                }),}),
]);
