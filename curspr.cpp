#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <io.h>

typedef struct {
    char name[100];
    char artist[100];
    int  year;
    float width;
    float height;
    char style[100];
} Picture;

void view(FILE* f);
void viewPic(Picture t);
void addPicture(FILE** f);
void editPicture(FILE** f);
int searchByName(FILE* f);
void deletePic(FILE** f);
void swap(FILE** f, int pos1, int pos2);
void sortByWidth(FILE** f);
void sortByName(FILE** f);
void sortByYear(FILE** f);
void searchByArtist(FILE* f);
void searchByYear(FILE** f);
int binarySearch(FILE* f, int year);
void styleReview(FILE** f);
void findThreeBiggest(FILE* f);
void saveToTxt(FILE* rep, Picture p);
int countPos(FILE* f);
int readInt();

int main() {
    char filename[100];
    FILE* f = nullptr;
    printf("------------------------------\n"
        "Gallery paintings accounting\n"
        "------------------------------\n");
    while (true) {
        printf("\nChoose the option:\n"
            " 1. New file\n"
            " 2. Open\n"
            " 3. View\n"
            " 4. Add picture\n"
            " 5. Edit\n"
            " 6. Delete picture\n"
            " 7. Sort\n"
            " 8. Search\n"
            " 9. Style review\n"
            "10. Find 3 biggest paintings\n"
            "11. Exit\n"
            "> ");
        int input = readInt();

        switch (input) {
        case 1: {
            printf("Enter file name: ");
            scanf_s("%99s", filename, (unsigned int)_countof(filename));
            if (f) fclose(f);
            errno_t ex = fopen_s(&f, filename, "rb");
            if (ex == 0) {
                printf("File with this name already exists. Do you want to rewrite it (y/n)?");
                char c;
                scanf_s(" %c", &c, 1u);
                if (c == 'y') {
                    fclose(f);
                    errno_t err1 = fopen_s(&f, filename, "wb");
                    if (err1 == 0 && f) printf("File was successfully created!\n");
                    else printf("File opening error!\n");
                    break;
                }
                else if (c == 'n') break;
                else {
                    printf("Error: invalid input!");
                    break;
                }
            }
            errno_t err1 = fopen_s(&f, filename, "wb+");
            if (err1 == 0 && f) printf("File was successfully created!\n");
            else printf("File opening error!\n");
            break;
        }
        case 2: {
            printf("Enter file name: ");
            scanf_s("%99s", filename, (unsigned)_countof(filename));
            if (f) fclose(f);
            errno_t err1 = fopen_s(&f, filename, "rb+");
            if (err1 == 0 && f) printf("File was successfully opened!\n");
            else printf("File opening error!\n");
            break;
        }
        case 3: {
            if (f) view(f);
            else printf("Error: no opened file!");
            break;
        }
        case 4: {
            if (f) addPicture(&f);
            else printf("Error: no opened file!");
            break;
        }
        case 5: {
            if (f) editPicture(&f);
            else printf("Error: no opened file!");
            break;
        }
        case 6: {
            if (f) deletePic(&f);
            else printf("Error: no opened file!");
            break;
        }
        case 7: {
            if (f) {
                printf("\nChoose sort type:\n1. Bubble sort by width \n2. Choice sort by name \n3. Insertion sort by year\n> ");
                int ch = readInt();
                switch (ch) {
                case 1: {
                    sortByWidth(&f);
                    break;
                }
                case 2: {
                    sortByName(&f);
                    break;
                }
                case 3: {
                    sortByYear(&f);
                    break;
                }
                default: {
                    printf("Error: invalid input!");
                    break;
                }
                }
            }
            else printf("Error: no opened file!");
            break;
        }
        case 8: {
            if (f) {
                printf("\nChoose search type:\n1. Linear search by artist \n2. Binary search by year\n> ");
                int ch = readInt();
                switch (ch) {
                case 1: {
                    searchByArtist(f);
                    break;
                }
                case 2: {
                    searchByYear(&f);
                    break;
                }
                default: {
                    printf("Error: invalid input!");
                    break;
                }
                }
            }
            else printf("Error: no opened file!");
            break;
        }

        case 9: {
            if (f) styleReview(&f);
            else printf("Error: no opened file!");
            break;
        }

        case 10: {
            if (f) findThreeBiggest(f);
            else printf("Error: no opened file!");
            break;
        }

        case 11: {
            return 0;
        }
        default: {
            printf("\nError: invalid input!");
            break;
        }
        }
    }
}

void view(FILE* f) {
    rewind(f);
    Picture temp;
    while (fread(&temp, sizeof(Picture), 1, f) == 1) viewPic(temp);
}

void viewPic(Picture t) {
    printf("\n%-10s %s", "Name:", t.name);
    printf("\n%-10s %s", "Artist:", t.artist);
    printf("\n%-10s %d", "Year:", t.year);
    printf("\n%-10s %.2f", "Width:", t.width);
    printf("\n%-10s %.2f", "Height:", t.height);
    printf("\n%-10s %s", "Style:", t.style);
    printf("\n* * *");
}

void addPicture(FILE** f) {
    Picture pd;
    bool valid = false;
    printf("Name: "); scanf_s(" %99[^\n]", pd.name, (unsigned)_countof(pd.name));
    printf("Author: "); scanf_s(" %99[^\n]", pd.artist, (unsigned)_countof(pd.artist));
    while (!valid) {
        printf("Year: ");
        if (!scanf_s("%d", &pd.year))
        {
            printf("\nError: invalid year!\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
        else valid = true;
    }
    valid = false;
    while (!valid) {
        printf("Width (m): ");
        if (!scanf_s("%f", &pd.width))
        {
            printf("\nError: invalid width!\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
        else valid = true;
    }
    valid = false;
    while (!valid) {
        printf("Height (m): ");
        if (!scanf_s("%f", &pd.height))
        {
            printf("\nError: invalid height!\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
        else valid = true;
    }
    printf("Style: "); scanf_s(" %99[^\n]", pd.style, (unsigned)_countof(pd.style));
    fseek(*f, 0, SEEK_END);
    fwrite(&pd, sizeof(Picture), 1, *f);
    fflush(*f);
    printf("Picture added.\n");
}

void editPicture(FILE** f) {
    int pos = searchByName(*f);
    if (pos == -1) printf("\nError: no matching results!\n");
    else {
        Picture p;
        bool valid = false;
        printf("\nChoose option for editing:\n"
            " 1. Name\n"
            " 2. Artist\n"
            " 3. Year\n"
            " 4. Width\n"
            " 5. Height\n"
            " 6. Style\n"
            "> ");
        int input = readInt();
        fseek(*f, pos * sizeof(Picture), SEEK_SET);
        fread(&p, sizeof(Picture), 1, *f);
        switch (input) {
        case 1: {
            printf("\nEnter new name: ");
            scanf_s(" %99[^\n]", p.name, (unsigned)_countof(p.name));
            break;
        }
        case 2: {
            printf("\nEnter new artist: ");
            scanf_s(" %99[^\n]", p.artist, (unsigned)_countof(p.artist));
            break;
        }
        case 3: {
            while (!valid) {
                printf("Enter new year: ");
                if (!scanf_s("%d", &p.year))
                {
                    printf("\nError: invalid year!\n");
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);
                }
                else valid = true;
            }
            break;
        }
        case 4: {
            while (!valid) {
                printf("Enter new width (m): ");
                if (!scanf_s("%f", &p.width))
                {
                    printf("\nError: invalid width!\n");
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);
                }
                else valid = true;
            }
            break;
        }
        case 5: {
            while (!valid) {
                printf("Enter new height (m): ");
                if (!scanf_s("%f", &p.height))
                {
                    printf("\nError: invalid height!\n");
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);
                }
                else valid = true;
            }
            break;
        }
        case 6: {
            printf("Enter new style: "); scanf_s(" %99[^\n]", p.style, (unsigned)_countof(p.style));
            break;
        }
        default: {
            printf("\nError: invalid input!\n");
            break;
        }
        }
        fseek(*f, pos * sizeof(Picture), SEEK_SET);
        fwrite(&p, sizeof(Picture), 1, *f);
    }
}

int searchByName(FILE* f) {
    int l = 0, t = 0;
    char target[100];
    Picture p;
    printf("\nEnter painting name: ");
    scanf_s(" %99[^\n]", target, (unsigned)_countof(target));
    do {
        fseek(f, l * sizeof(Picture), SEEK_SET);
        t = fread(&p, sizeof(Picture), 1, f);
        l++;
    } while (strcmp(p.name, target) != 0 && t != 0);
    if (t == 0) return -1;
    return l - 1;
}

void deletePic(FILE** f) {
    int pos = searchByName(*f);
    int n = countPos(*f);
    if (pos == -1) printf("\nError: no matching results!\n");
    else {
        while (pos < n - 1)
        {
            swap(f, pos, pos + 1);
            pos++;
        }
        fflush(*f);
        int d = _fileno(*f);
        _chsize_s(d, pos * sizeof(Picture));
    }
}

void swap(FILE** f, int pos1, int pos2) {
    Picture p1, p2;
    fseek(*f, pos1 * sizeof(Picture), SEEK_SET);
    fread(&p1, sizeof(Picture), 1, *f);
    fseek(*f, pos2 * sizeof(Picture), SEEK_SET);
    fread(&p2, sizeof(Picture), 1, *f);
    fseek(*f, pos1 * sizeof(Picture), SEEK_SET);
    fwrite(&p2, sizeof(Picture), 1, *f);
    fseek(*f, pos2 * sizeof(Picture), SEEK_SET);
    fwrite(&p1, sizeof(Picture), 1, *f);
}

void sortByWidth(FILE** f) {
    int n = countPos(*f);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            fseek(*f, j * sizeof(Picture), SEEK_SET);
            Picture p1, p2;
            fread(&p1, sizeof(Picture), 1, *f);
            fread(&p2, sizeof(Picture), 1, *f);
            if (p1.width > p2.width) swap(f, j, j + 1);
        }
    }
}

void sortByName(FILE** f) {
    int n = countPos(*f);
    for (int i = 0; i < n; i++) {
        Picture t, min;
        int minPos = i;
        fseek(*f, i * sizeof(Picture), SEEK_SET);
        fread(&min, sizeof(Picture), 1, *f);
        for (int j = i + 1; j < n; j++) {
            fread(&t, sizeof(Picture), 1, *f);
            if (strcmp(min.name, t.name) > 0) {
                min = t;
                minPos = j;
            }
        }
        swap(f, i, minPos);
    }
}

void sortByYear(FILE** f) {
    int n = countPos(*f);
    for (int i = 1; i < n; i++) {
        Picture t, cur;
        fseek(*f, i * sizeof(Picture), SEEK_SET);
        fread(&cur, sizeof(Picture), 1, *f);
        int j = i - 1;
        while (j >= 0) {
            fseek(*f, j * sizeof(Picture), SEEK_SET);
            fread(&t, sizeof(Picture), 1, *f);
            if (t.year <= cur.year) break;
            fseek(*f, (j + 1) * sizeof(Picture), SEEK_SET);
            fwrite(&t, sizeof(Picture), 1, *f);
            j--;
        }
        fseek(*f, (j + 1) * sizeof(Picture), SEEK_SET);
        fwrite(&cur, sizeof(Picture), 1, *f);
    }
}

void searchByArtist(FILE* f) {
    int n = countPos(f);
    char target[100];
    Picture p;
    bool found = false;
    printf("\nEnter artist: ");
    scanf_s(" %99[^\n]", target, (unsigned)_countof(target));
    printf("\n%-10s %s", "Artist:", target);
    for (int i = 0; i < n; i++) {
        fread(&p, sizeof(Picture), 1, f);
        if (strcmp(p.artist, target) == 0) {
            viewPic(p);
            found = true;
        }
    }
    if (!found) printf("\nNo results!\n");
}

void searchByYear(FILE** f) {
    sortByYear(f);
    int y1 = 0, y2 = 0, pos1, pos2;
    bool valid = false;
    Picture t;
    while (!valid) {
        printf("Enter search start: ");
        if (!scanf_s("%d", &y1))
        {
            printf("\nError: invalid year!\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
        else valid = true;
    }
    valid = false;
    while (!valid) {
        printf("Enter search end: ");
        if (!scanf_s("%d", &y2))
        {
            printf("\nError: invalid year!\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
        else valid = true;
    }
    pos1 = binarySearch(*f, y1);
    pos2 = binarySearch(*f, y2);
    if (pos1 != -1 && pos2 != -1 && pos1 <= pos2)
    {
        fseek(*f, pos1 * sizeof(Picture), SEEK_SET);
        while (pos1 < pos2 + 1) {
            Picture t;
            fread(&t, sizeof(Picture), 1, *f);
            viewPic(t);
            pos1++;
        }
    }
    else printf("Error: no matching results!");
}

int binarySearch(FILE* f, int year) {
    bool found = false;
    Picture t;
    int n = countPos(f), start = 0, end = n, pos;
    while (!found && start <= end) {
        pos = start + (end - start) / 2;
        fseek(f, pos * sizeof(Picture), SEEK_SET);
        fread(&t, sizeof(Picture), 1, f);
        if (year > t.year) start = pos + 1;
        else if (year < t.year) end = pos - 1;
        else if (year == t.year) found = true;
    }
    if (found) return pos;
    else return -1;
}

void styleReview(FILE** f) {
    int n = countPos(*f);
    if (n == 0) printf("\nFile is empty!\n");
    else {
        int l = 1;
        while (l < n) {
            FILE* temp;
            fopen_s(&temp, "buf.bin", "wb+");
            rewind(*f);
            rewind(temp);
            int b1 = 0;
            while (b1 < n)
            {
                int b2 = b1 + l;
                int pos1 = 0, pos2 = 0;
                int len1 = (b2 <= n) ? l : (n - b1);
                int len2 = (b2 + l <= n) ? l : (n - b2);
                if (len2 < 0) len2 = 0;
                Picture p1, p2;
                fseek(*f, (pos1 + b1) * sizeof(Picture), SEEK_SET);
                fread(&p1, sizeof(Picture), 1, *f);
                fseek(*f, (pos2 + b2) * sizeof(Picture), SEEK_SET);
                fread(&p2, sizeof(Picture), 1, *f);
                while (pos1 < len1 && pos2 < len2) {
                    if (strcmp(p1.style, p2.style) < 0 || (strcmp(p1.style, p2.style) == 0 && strcmp(p1.name, p2.name) < 0)) {
                        fwrite(&p1, sizeof(Picture), 1, temp);
                        pos1++;
                        fseek(*f, (pos1 + b1) * sizeof(Picture), SEEK_SET);
                        fread(&p1, sizeof(Picture), 1, *f);
                    }
                    else {
                        fwrite(&p2, sizeof(Picture), 1, temp);
                        pos2++;
                        fseek(*f, (pos2 + b2) * sizeof(Picture), SEEK_SET);
                        fread(&p2, sizeof(Picture), 1, *f);
                    }
                }
                while (pos1 < len1) {
                    Picture p1;
                    fseek(*f, (pos1 + b1) * sizeof(Picture), SEEK_SET);
                    fread(&p1, sizeof(Picture), 1, *f);
                    fwrite(&p1, sizeof(Picture), 1, temp);
                    pos1++;
                }
                while (pos2 < len2) {
                    Picture p2;
                    fseek(*f, (pos2 + b2) * sizeof(Picture), SEEK_SET);
                    fread(&p2, sizeof(Picture), 1, *f);
                    fwrite(&p2, sizeof(Picture), 1, temp);
                    pos2++;
                }
                b1 += 2 * l;
            }
            rewind(*f);
            rewind(temp);
            for (int i = 0; i < n; i++) {
                Picture p;
                fread(&p, sizeof(Picture), 1, temp);
                fwrite(&p, sizeof(Picture), 1, *f);
            }
            fclose(temp);
            remove("buf.bin");
            l *= 2;
        }
        rewind(*f);
        char curStyle[100] = "";
        Picture p;
        while (fread(&p, sizeof(Picture), 1, *f)) {
            if (strcmp(curStyle, p.style) != 0) {
                strcpy_s(curStyle, p.style);
                printf("\n%s\n--------------------", curStyle);
            }
            viewPic(p);
        }
        char ch;
        printf("\nSave result to txt (y/n)?\n> ");
        scanf_s(" %c", &ch, 1u);
        if (ch == 'y') {
            FILE* rep;
            errno_t err = fopen_s(&rep, "report.txt", "w");
            if (err == 0) {
                rewind(*f);
                Picture p;
                while (fread(&p, sizeof(Picture), 1, *f)) {
                    if (strcmp(curStyle, p.style) != 0) {
                        strcpy_s(curStyle, p.style);
                        fprintf(rep, "\n%s\n--------------------", curStyle);
                    }
                    saveToTxt(rep, p);
                }
                fclose(rep);
            }
            else printf("\nError: could not open .txt file!\n");
        }
        else if (ch == 'n') printf("\nCancelled!\n");
        else printf("\nError: invalid input\n");
    }
}

void findThreeBiggest(FILE* f) {
    int n = countPos(f);
    Picture pic1 = { 0 }, pic2 = { 0 }, pic3 = { 0 };
    double s1 = 0, s2 = 0, s3 = 0;
    if (n == 0) printf("\nFile is empty!\n");
    else {
        Picture t;
        for (int i = 0; i < n; i++) {
            fread(&t, sizeof(Picture), 1, f);
            double s = t.width * t.height;
            if (s > s1) {
                pic3 = pic2;
                s3 = s2;
                pic2 = pic1;
                s2 = s1;
                pic1 = t;
                s1 = s;
            }
            else if (s > s2) {
                pic3 = pic2;
                s3 = s2;
                pic2 = t;
                s2 = s;
            }
            else if (s > s3) {
                pic3 = t;
                s3 = s;
            }
        }
        printf("\nThree largest paintings:\n------------------------------"
            "\n1st place: ");
        printf("\n%-10s %.2f", "Area:", s1);
        viewPic(pic1);
        if (s2 != 0)
        {
            printf("\n2nd place: ");
            printf("\n%-10s %.2f", "Area:", s2);
            viewPic(pic2);
        }
        if (s3 != 0)
        {
            printf("\n3rd place: ");
            printf("\n%-10s %.2f", "Area:", s3);
            viewPic(pic3);
        }
        char ch;
        printf("\nSave result to txt (y/n)?\n> ");
        scanf_s(" %c", &ch, 1u);
        if (ch == 'y') {
            FILE* rep;
            errno_t err = fopen_s(&rep, "report.txt", "w");
            if (err == 0) {
                saveToTxt(rep, pic1);
                if (n > 1) saveToTxt(rep, pic2);
                if (n > 2) saveToTxt(rep, pic3);
                fclose(rep);
            }
            else printf("\nError: could not create .txt file!\n");
        }
        else if (ch == 'n') printf("\nCancelled!\n");
        else printf("Error: invalid input");
    }
}

void saveToTxt(FILE* rep, Picture p) {
    fprintf(rep, "\n%-10s %s", "Name:", p.name);
    fprintf(rep, "\n%-10s %s", "Artist:", p.artist);
    fprintf(rep, "\n%-10s %d", "Year:", p.year);
    fprintf(rep, "\n%-10s %.2f", "Width:", p.width);
    fprintf(rep, "\n%-10s %.2f", "Height:", p.height);
    fprintf(rep, "\n%-10s %s", "Style:", p.style);
    fprintf(rep, "\n* * *");
}

int countPos(FILE* f) {
    fseek(f, 0, SEEK_END);
    int n = ftell(f) / sizeof(Picture);
    rewind(f);
    return n;
}

int readInt() {
    int a;
    while (scanf_s("%d", &a) != 1) {
        printf("Error: invalid input!\n");
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
    return a;
}
