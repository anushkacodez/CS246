#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student{
    char roll_no[100];
    char name[100];

};

struct course{
    char course_name[6];
    char credits[3];
    char semester[3];
};

struct grade{
    char roll_no[100];
    char course_name[6];
    char gradeReceived[3];
    char semester_time[100];
    char semester[3];
};

struct no_dues{
    char roll_no[100];
    char hostel[4];
    char department[4];
    char ncc[4];
    char cos[4];
    char nso[4];
    char institute[4];
};

struct disiplinary{
    char roll_no[100];
    char action[10];
};

typedef struct student* studentptr;
typedef struct course* courseptr;
typedef struct grade* gradeptr;
typedef struct no_dues* noDuesptr;
typedef struct disiplinary* disciplinaryptr;


studentptr students_list[125];
courseptr course_list[64];
gradeptr grade_list[7600];
noDuesptr no_dues_list[125];
disciplinaryptr disciplinary_list[120];



void readStudentCSV()
{
    FILE *f1=fopen("students.csv", "r");
    if(f1==NULL)
    {
        printf("Error in opening file!\n");
        return;
    }

    char buffer[2000];
    fgets(buffer, 2000, f1);

    for(int i=0; i<120; i++)
    {
        students_list[i]=(studentptr)malloc(sizeof(struct student));
        fgets(buffer, 2000, f1);
        char * token=strtok(buffer, ",");
        int column=0;

        while(token!=NULL)
        {
            if(column==0)
            {
                strcpy(students_list[i]->roll_no, token);
            }
            else if(column==1)
            {
                strcpy(students_list[i]->name, token);
            }
            token = strtok(NULL, ",");
            column++;
        }
    }
    fclose(f1);
    return;
}

void printStudentsCSV()
{
    for(int i=0; i<120; i++)
    {
        printf("%d %s %s", i+1, students_list[i]->roll_no, students_list[i]->name);
    }
    return;
}


void readCurriculumCSV()
{
    FILE *f2=fopen("curriculum.csv", "r");
    if(f2==NULL)
    {
        printf("Error in opening file!\n");
        return;
    }

    char buffer[2000];
    fgets(buffer, 2000, f2);

    for(int i=0; i<64; i++)
    {
        course_list[i]=(courseptr)malloc(sizeof(struct course));
        fgets(buffer, 2000, f2);
        char * token=strtok(buffer, ",");
        int column=0;

        while(token!=NULL)
        {
            if(column==0)
            {
                strcpy(course_list[i]->course_name, token);
            }
            else if(column==1)
            {
                strcpy(course_list[i]->credits, token);
            }
            else if(column==2)
            {
                strcpy(course_list[i]->semester, token);
            }
            token = strtok(NULL, ",");
            column++;
        }
    }
    fclose(f2);
    return;
}

void printCurriculumCSV()
{
    for(int i=0; i<63; i++)
    {
        printf("%d %s %s %s", i+1, course_list[i]->course_name, course_list[i]->credits,course_list[i]->semester);
    }
    return;
}



void readGradeCSV()
{
    FILE *f3=fopen("grade.csv", "r");
    if(f3==NULL)
    {
        printf("Error in opening file!\n");
        return;
    }

    char buffer[2000];
    fgets(buffer, 2000, f3);

    for(int i=0; i<7562; i++)
    {
        grade_list[i]=(gradeptr)malloc(sizeof(struct grade));
        fgets(buffer, 2000, f3);
        char * token=strtok(buffer, ",");
        int column=0;

        while(token!=NULL)
        {
            if(column==0)
            {
                strcpy(grade_list[i]->roll_no, token);
            }
            else if(column==1)
            {
                strcpy(grade_list[i]->course_name, token);
            }
            else if(column==2)
            {
                strcpy(grade_list[i]->gradeReceived, token);
            }
            else if(column==3)
            {
                strcpy(grade_list[i]->semester_time, token);
            }
            token = strtok(NULL, ",");
            column++;
        }
    }
    fclose(f3);
    return;
}

void printGradeCSV()
{
    for(int i=0; i<7562; i++)
    {
        printf("%d %s %s %s %s", i+1, grade_list[i]->roll_no, grade_list[i]->course_name, grade_list[i]->gradeReceived, grade_list[i]->semester_time);
    }
    return;
}


void readNoDuesCSV()
{
    FILE *f4=fopen("no-dues.csv", "r");
    if(f4==NULL)
    {
        printf("Error in opening file!\n");
        return;
    }

    char buffer[2000];
    fgets(buffer, 2000, f4);

    for(int i=0; i<120; i++)
    {
        no_dues_list[i]=(noDuesptr)malloc(sizeof(struct no_dues));
        fgets(buffer, 2000, f4);
        char * token=strtok(buffer, ",");
        int column=0;

        while(token!=NULL)
        {
            if(column==0)
            {
                strcpy(no_dues_list[i]->roll_no, token);
            }
            else if(column==1)
            {
                strcpy(no_dues_list[i]->hostel, token);
            }
            else if(column==2)
            {
                strcpy(no_dues_list[i]->department, token);
            }
            else if(column==3)
            {
                strcpy(no_dues_list[i]->ncc, token);
            }
            else if(column==4)
            {
                strcpy(no_dues_list[i]->cos, token);
            }
            else if(column==5)
            {
                strcpy(no_dues_list[i]->nso, token);
            }
            else if(column==6)
            {
                strcpy(no_dues_list[i]->institute, token);
            }
            token = strtok(NULL, ",");
            column++;
        }
    }
    fclose(f4);
    return;
}

void printNoDuesCSV()
{
    for(int i=0; i<120; i++)
    {
        printf("%d %s %s %s %s %s %s %s", i+1, no_dues_list[i]->roll_no, no_dues_list[i]->hostel, no_dues_list[i]->department, no_dues_list[i]->ncc, no_dues_list[i]->cos, no_dues_list[i]->nso, no_dues_list[i]->institute);
    }
    return;
}



void readDisciplinaryCSV()
{
    FILE *f5=fopen("disciplinary.csv", "r");
    if(f5==NULL)
    {
        printf("Error in opening file!\n");
        return;
    }
    
    char buffer[2000];
    fgets(buffer, 2000, f5);

    for(int i=0; i<120; i++)
    {
        disciplinary_list[i]=(disciplinaryptr)malloc(sizeof(struct disiplinary));
        fgets(buffer, 2000, f5);
        char * token=strtok(buffer, ",");
        int column=0;
        
        while(token!=NULL)
        {
            //printf("%s", token);
            //printf("ok\n");
            // char buffer2[200];
            // printf("%ld", sizeof(token));
            //for(int j=0; j<sizeof(token); j++)
            // {
            //     buffer2[j]=token[j];
            // }
            if(column==0)
            {
                // for(int j=0; j<sizeof(token); j++)
                // {
                //     disciplinary_list[i]->roll_no[j]=buffer2[j];
                // }
                
                strcpy(disciplinary_list[i]->roll_no, token);
            }
            // else if(column==1)
            // {
            //     printf("%s", token);
            // }
            else if(column==1)
            {
                // for(int j=0; j<sizeof(token); j++)
                // {
                //     disciplinary_list[i]->action[j]=buffer2[j];
                // }
                strcpy(disciplinary_list[i]->action, token);
            }
            
            token = strtok(NULL, ",");
            column++;
        }
    }
    fclose(f5);
    return;
}

void printDisciplinaryCSV()
{
    for(int i=0; i<120; i++)
    {
        printf("%d %s %s", i+1, disciplinary_list[i]->roll_no,disciplinary_list[i]->action);
    }
    return;
}

struct failing{
    char roll_no[100];
    int core_course;
    gradeptr core_failed[63];
    int elective_course;
    gradeptr electivefailed[63];
    int hss;
    gradeptr hss_failed[63];
    int sa;
    gradeptr sa_failed[63];
    int credits;
};

typedef struct failing* failingptr;

int getCredits(gradeptr grade)
{
    for(int i=0; i<63; i++)
    {   
        if(strcmp(course_list[i]->course_name, grade->course_name)==0)
        {
            int cred=0;
            int x=1;
            //int sz=sizeof(course_list[i]->credits)-1;
            //printf("%d", sz);
            for(int j=1; j>=0 ;j++)
            {   
                //printf("%c", course_list[i]->credits[j]);
                // if(course_list[i]->credits[j]!='\n')
                // {
                //     cred+=((course_list[i]->credits[j])-'0')*x;
                //     x=x*10;
                // }

            }
            return cred;
        }
        
    }
    return 0;
}
void checkCoreCourseRequirement(char* s)
{
    failingptr failhora=(failingptr)malloc(sizeof(struct failing));
    failhora->core_course=0;
    failhora->elective_course=0;
    failhora->hss=0;
    failhora->sa=0;

    for(int i=0; i<7562; i++)
    {
        if(strcmp(grade_list[i]->roll_no, s)==0)
        {
            if(strcmp(grade_list[i]->semester_time, "Aug 2027 - Dec 2027")==0)
            {
                if(strcmp(grade_list[i]->gradeReceived,"FP")==0)
                {
                    failhora->core_failed[failhora->core_course]=grade_list[i];
                    failhora->core_course++;
                }
            }
        }
    }
}

void solve()
{
    while(1){
        printf("Write 'quit' to end loop\n");
        char s[10];
        scanf("%s", s);

        if(strcmp(s, "quit") == 0)
        {
            break;
        } 
        if(s[0]=='\n')
        {
            
        }
        else{
            checkCoreCourseRequirement(s);
        }
    }
}

int main()
{
    printf("students.csv\n\n");
    readStudentCSV();
    printStudentsCSV();
    
    printf("\ncurriculum.csv\n\n");
    readCurriculumCSV();
    printCurriculumCSV();


    printf("\ngrade.csv\n\n");
    readGradeCSV();
    printGradeCSV();


    printf("\nno-dues.csv\n\n");
    readNoDuesCSV();
    printNoDuesCSV();

    printf("\ndisciplinary.csv\n\n");

    readDisciplinaryCSV();
    printDisciplinaryCSV();
    printf("\n");


    //int ans=getCredits(grade_list[0]);
    //printf("%d", ans);
    return 0;
}