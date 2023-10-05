/*
 * @Author: 雪风@mud.ren
 * @Date: 2022-03-29 10:38:10
 * @LastEditTime: 2022-03-29 11:16:56
 * @LastEditors: 雪风
 * @Description: 文件读取与处理相关模拟函数
 *  https://bbs.mud.ren
 */

// 判断文件是否存在
int file_exists(string file)
{
    return (file_size(file) >= 0);
}

string *read_lines(string file)
{
    if (file_exists(file))
    {
        return filter_array(explode(read_file(file), "\n"), (: trim($1) != "" && $1[0] != '#' && $1[0] != ';' :));
    }
    else
        error("文件 " + file + " 不存在！");
}

//如果file不存在，则新建文件file
void assure_file(string file)
{
    string path, dir, *dirs;

    if (file_size(file) != -1)//-1，文件不存在；-2，表示是个目录。
        return;

    dirs = explode(file, "/");//把字符串file打散成一个字符串数组，打散标志为’/‘

    if (file[strlen(file) - 1] != '/')
    {
        dirs = dirs[0..sizeof(dirs)-2];//之前的路径是文件，这里取得目录。
    }

    path = "";

    foreach (dir in dirs)
    {
        if (dir == "")
            continue;
        path += "/" + dir;

        switch (file_size(path))
        {
        case -1://-1代表path不存在
            mkdir(path);
            break;
        case -2://-2代表path是一个目录
            continue;
        default:
            return;
        }
    }
}

void log_file(string file, string text, int flag)
{
    assure_file(LOG_DIR + file);
    write_file(LOG_DIR + file, text, flag);
}

void cat(string file)
{
    write(read_file(file));
}

int tail(string path)
{
    if (stringp(path) && file_size(path) >= 0)
    {
        write(read_file(path, file_length(path) - 9));
        return 1;
    }

    return 0;
}

mixed lpc_file(string str)
{
    if (!file_exists(str))
    {
        if (file_exists(str + ".c"))
            return str + ".c";
        else
            return 0;
    }
    else
        return str;
}
