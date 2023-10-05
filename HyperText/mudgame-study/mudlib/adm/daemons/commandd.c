//
// cmd_d.c
//
// By Annihilator (11/07/94)
// Update by Doing Lu

#pragma optimize
// #pragma save_binary

mapping search = ([]);

void rehash(string dir)
{
    int i;
    string path;
    string *cmds;
    mapping cmdlist;
    string alias;

    if (!sscanf(dir, "/cmds/%s", path) && !sscanf(dir, "/mudcore/cmds/%s", path))
    {
        write("The path(" + dir + ")was not command path, "
                                  "operation was failed.\n");
        /*
            The path(/cmds/adm/)was not command path, operation was failed.
            The path(/cmds/arch/)was not command path, operation was failed.
            The path(/cmds/wiz/)was not command path, operation was failed.
            The path(/cmds/imm/)was not command path, operation was failed.
            The path(/cmds/usr/)was not command path, operation was failed.
            The path(/cmds/std/)was not command path, operation was failed.
            The path(/cmds/skill/)was not command path, operation was failed.
            The path(/cmds/test/)was not command path, operation was failed.
            The path(/mudcore/cmds/wizard/)was not command path, operation was failed.
            The path(/mudcore/cmds/player/)was not command path, operation was failed.
        */
        return;
    }

    if (dir[sizeof(dir) - 1] != '/')
        dir += "/";
    cmds = get_dir(dir);
    i = sizeof(cmds);
    cmdlist = allocate_mapping(i);

    // 取所有命令
    while (i--)
        if (sscanf(cmds[i], "%s.c", cmds[i]))
            cmdlist[cmds[i]] = dir + cmds[i] + ".c";

    // 取所有命令的别名
    i = sizeof(cmds);
    while (i--)
        if (sscanf(cmds[i], "%s.alias", cmds[i]))
        {
            alias = read_file(dir + cmds[i] + ".alias", 1, 1);
            alias = replace_string(alias, "\n", "");
            alias = replace_string(alias, "\r", "");
            sscanf(alias, "%s.c", alias);
            if (member_array(alias, cmds) != -1)
                cmdlist[cmds[i]] = dir + alias + ".c";
        }

    if (sizeof(cmds))
        search[dir] = cmdlist;
}

string find_command(string verb, string *path)
{
    int i;
    string file;
    mapping current;

    //write(sprintf("%O\n", path));
    //结果：
    //({ /* sizeof() == 10 */
    //"/cmds/adm/",
    //"/cmds/arch/",
    //"/cmds/wiz/",
    //"/cmds/imm/",
    //"/cmds/usr/",
    //"/cmds/std/",
    //"/cmds/skill/",
    //"/cmds/test/",
    //"/mudcore/cmds/wizard/",
    //"/mudcore/cmds/player/"
    //})
    if (!pointerp(path))
        return 0;

    for (i = 0; i < sizeof(path); i++)
    {
        if (undefinedp(current = search[path[i]]))
        {
            rehash(path[i]);
            if (undefinedp(current = search[path[i]]))
                continue;
        }
        if (stringp(file = current[verb]))
            return file;
    }
    return 0;
}
