/**
 * 数据保存接口
 */
// void create(){}

int save()
{
    string file;

    if (stringp(file = this_object()->query_save_file()))
    {
        assure_file(file);//mudcore中的sefun函数。\mudcore\system\kernel\simul_efun\file.c
        return save_object(file);//把物件的变量值储存到file文件中。efun函数
    }

    return 0;
}

int restore()
{
    string file;

    //write(sprintf(">>>>restore()中的this_object()此时指的是：%O<<<<\n", this_object()));
    if (stringp(file = this_object()->query_save_file()))
    {
        //write(sprintf(">>>>restore()中的file此时的值是：%O<<<<\n", file));
        return restore_object(file);//把物件的变量值从file文件中读取出来。efun函数
    } 

    return 0;
}
