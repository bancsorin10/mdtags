
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>


void parse_file(int tags, const char name[256]) {
    
    // check if file is .md
    int i = 0;
    int j = 0;
    char filename[256];
    FILE *f;
    char *line;
    size_t ll;

    // prefix filename info
    // filenames can be ordered with numbers like 3005_scrap_file.md
    // the numbering can be ignored thus making the tags easier to use
    int pre_fn = 0;

    while (name[i++]) {
    }
    i--;
    if (!(name[i-1] == 'd' && name[i-2] == 'm' && name[i-3] == '.')) {
        return ;
    }

    i -= 3;
    bzero(filename, 256);
    mempcpy(filename, name, i);

    // check prefix
    while (filename[pre_fn] && filename[pre_fn] >= '0' &&
           filename[pre_fn] <= '9') {
        ++pre_fn;
    }
    // skip the `_` if there was a prefix
    if (pre_fn) {
        ++pre_fn;
    }

    // add tag to the file itself
    dprintf(tags, "[[%s]]\t%s\t1\n", filename + pre_fn, name);


    // add tags for headers
    f = fopen(name, "r");
    while (getline(&line, &ll, f) != -1) {
        if (ll == 0) {
            continue;
        }
        if (line[0] != '#') {
            continue;
        }

        i = 0;
        while (line[i++] != ' ') ;
        // ++i;
        j = i;
        while (line[j]) {
            if (line[j] == '\n') {
                line[j] = 0;
            }
            ++j;
        }

        dprintf(tags, "[[%s#%s]]\t%s\t/^#\\{1,\\} %s/\n", filename + pre_fn,
                line + i, name, line + i);
    }

    fclose(f);
}

void parse_dir(DIR *dir) {

    struct dirent *fdirent;
    int tags;

    // open file for tags
    tags = open("tags", O_CREAT | O_RDWR,
              S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);


    while ((fdirent = readdir(dir)) != NULL) {
        if (fdirent->d_type != DT_REG){
            continue;
        }

        // we have a regular file
        parse_file(tags, fdirent->d_name);
    }

    close(tags);
}

int main() {
    DIR *dir;

    dir = opendir(".");

    parse_dir(dir);

    closedir(dir);
    return 0;
}
