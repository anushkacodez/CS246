#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void compute_cpi(char roll_number[11], MYSQL *conn)
{
    char query[400];
    sprintf(query, "SELECT* from course18 natural join grade18 where roll_number='%s'", roll_number);
    //printf("%s\n", query);
    if (mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }

    MYSQL_RES *result = mysql_store_result(conn);

    if (result == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }

    int num_fields = mysql_num_fields(result);

    MYSQL_ROW row;
    int spi1=0;
    int spi2=0;
    int spi3=0;
    int spi4=0;
    int spi5=0;
    int spi6=0;
    int spi7=0;
    int spi8=0;

    int total_cred_1=0;
    int total_cred_2=0;
    int total_cred_3=0;
    int total_cred_4=0;
    int total_cred_5=0;
    int total_cred_6=0;
    int total_cred_7=0;
    int total_cred_8=0;
    while ((row = mysql_fetch_row(result)))
    {
        int course_cred=atoi(row[6]);
        int sem=atoi(row[1]);
        //printf("%d",sem);
        if(sem==1)
        {
            total_cred_1+=course_cred;
                if(!strcmp(row[8],"AA"))
            {
                spi1+=course_cred*10;
            }
            else if(!strcmp(row[8],"AB"))
            {
                spi1+=course_cred*9;
            }
            else if(!strcmp(row[8],"BB"))
            {
                spi1+=course_cred*8;
            }
            else if(!strcmp(row[8],"BC"))
            {
                spi1+=course_cred*7;
            }
            else if(!strcmp(row[8],"CC"))
            {
                spi1+=course_cred*6;
            }
            else if(!strcmp(row[8],"CD"))
            {
                spi1+=course_cred*5;
            }
            else if(!strcmp(row[8],"DD"))
            {
                spi1+=course_cred*4;
            }
    
        }
        else if(sem==2)
        {
            total_cred_2+=course_cred;
            if(!strcmp(row[8],"AA"))
        {
            spi2+=course_cred*10;
        }
        else if(!strcmp(row[8],"AB"))
        {
            spi2+=course_cred*9;
        }
        else if(!strcmp(row[8],"BB"))
        {
            spi2+=course_cred*8;
        }
        else if(!strcmp(row[8],"BC"))
        {
            spi2+=course_cred*7;
        }
        else if(!strcmp(row[8],"CC"))
        {
            spi2+=course_cred*6;
        }
        else if(!strcmp(row[8],"CD"))
        {
            spi2+=course_cred*5;
        }
        else if(!strcmp(row[8],"DD"))
        {
            spi2+=course_cred*4;
        }
        }
        else if(sem==3)
        {
            total_cred_3+=course_cred;
            if(!strcmp(row[8],"AA"))
        {
            spi3+=course_cred*10;
        }
        else if(!strcmp(row[8],"AB"))
        {
            spi3+=course_cred*9;
        }
        else if(!strcmp(row[8],"BB"))
        {
            spi3+=course_cred*8;
        }
        else if(!strcmp(row[8],"BC"))
        {
            spi3+=course_cred*7;
        }
        else if(!strcmp(row[8],"CC"))
        {
            spi3+=course_cred*6;
        }
        else if(!strcmp(row[8],"CD"))
        {
            spi3+=course_cred*5;
        }
        else if(!strcmp(row[8],"DD"))
        {
            spi3+=course_cred*4;
        }
        }
        else if(sem==4)
        {
            total_cred_4+=course_cred;
            if(!strcmp(row[8],"AA"))
        {
            spi4+=course_cred*10;
        }
        else if(!strcmp(row[8],"AB"))
        {
            spi4+=course_cred*9;
        }
        else if(!strcmp(row[8],"BB"))
        {
            spi4+=course_cred*8;
        }
        else if(!strcmp(row[8],"BC"))
        {
            spi4+=course_cred*7;
        }
        else if(!strcmp(row[8],"CC"))
        {
            spi4+=course_cred*6;
        }
        else if(!strcmp(row[8],"CD"))
        {
            spi4+=course_cred*5;
        }
        else if(!strcmp(row[8],"DD"))
        {
            spi4+=course_cred*4;
        }
        }
        else if(sem==5)
        {
            total_cred_5+=course_cred;
            if(!strcmp(row[8],"AA"))
        {
            spi5+=course_cred*10;
        }
        else if(!strcmp(row[8],"AB"))
        {
            spi5+=course_cred*9;
        }
        else if(!strcmp(row[8],"BB"))
        {
            spi5+=course_cred*8;
        }
        else if(!strcmp(row[8],"BC"))
        {
            spi5+=course_cred*7;
        }
        else if(!strcmp(row[8],"CC"))
        {
            spi5+=course_cred*6;
        }
        else if(!strcmp(row[8],"CD"))
        {
            spi5+=course_cred*5;
        }
        else if(!strcmp(row[8],"DD"))
        {
            spi5+=course_cred*4;
        }
        }
        else if(sem==6)
        {
            total_cred_6+=course_cred;
            if(!strcmp(row[8],"AA"))
        {
            spi6+=course_cred*10;
        }
        else if(!strcmp(row[8],"AB"))
        
        {
            spi6+=course_cred*7;
        }
        else if(!strcmp(row[8],"CC"))
        {
            spi6+=course_cred*6;
        }
        else if(!strcmp(row[8],"CD"))
        {
            spi6+=course_cred*5;
        }
        else if(!strcmp(row[8],"DD"))
        {
            spi6+=course_cred*4;
        }
        }
        else if(sem==7)
        {
            total_cred_7+=course_cred;
            if(!strcmp(row[8],"AA"))
        {
            spi7+=course_cred*10;
        }
        else if(!strcmp(row[8],"AB"))
        {
            spi7+=course_cred*9;
        }
        else if(!strcmp(row[8],"BB"))
        {
            spi7+=course_cred*8;
        }
        else if(!strcmp(row[8],"BC"))
        {
            spi7+=course_cred*7;
        }
        else if(!strcmp(row[8],"CC"))
        {
            spi7+=course_cred*6;
        }
        else if(!strcmp(row[8],"CD"))
        {
            spi7+=course_cred*5;
        }
        else if(!strcmp(row[8],"DD"))
        {
            spi7+=course_cred*4;
        }
        }
        else if(sem==8)
        {
            total_cred_8+=course_cred;
            if(!strcmp(row[8],"AA"))
        {
            spi8+=course_cred*10;
        }
        else if(!strcmp(row[8],"AB"))
        {
            spi8+=course_cred*9;
        }
        else if(!strcmp(row[8],"BB"))
        {
            spi8+=course_cred*8;
        }
        else if(!strcmp(row[8],"BC"))
        {
            spi8+=course_cred*7;
        }
        else if(!strcmp(row[8],"CC"))
        {
            spi8+=course_cred*6;
        }
        else if(!strcmp(row[8],"CD"))
        {
            spi8+=course_cred*5;
        }
        else if(!strcmp(row[8],"DD"))
        {
            spi8+=course_cred*4;
        }
        }
    
        
        //printf("\n");
    }

    
    //printf("%d\n", spi1);
    float tot_spi_1=((float)spi1/(float)total_cred_1);
    float tot_spi_2=((float)spi2/(float)total_cred_2);
    float tot_spi_3=((float)spi3/(float)total_cred_3);
    float tot_spi_4=((float)spi4/(float)total_cred_4);
    float tot_spi_5=((float)spi5/(float)total_cred_5);
    float tot_spi_6=((float)spi6/(float)total_cred_6);
    float tot_spi_7=((float)spi7/(float)total_cred_7);
    float tot_spi_8=((float)spi8/(float)total_cred_8);

    float cpi1=((float)spi1/total_cred_1);
    float cpi2=(float)(spi1+spi2)/(float)(total_cred_1+total_cred_2);
    float cpi3=(float)(spi1+spi2+spi3)/(float)(total_cred_1+total_cred_2+total_cred_3);
    float cpi4=(float)(spi1+spi2+spi3+spi4)/(float)(total_cred_1+total_cred_2+total_cred_3+total_cred_4);
    float cpi5=(float)(spi1+spi2+spi3+spi4+spi5)/(float)(total_cred_1+total_cred_2+total_cred_3+total_cred_4+total_cred_5);
    float cpi6=(float)(spi1+spi2+spi3+spi4+spi5+spi6)/(float)(total_cred_1+total_cred_2+total_cred_3+total_cred_4+total_cred_5+total_cred_6);
    float cpi7=(float)(spi1+spi2+spi3+spi4+spi5+spi6+spi7)/(float)(total_cred_1+total_cred_2+total_cred_3+total_cred_4+total_cred_5+total_cred_6+total_cred_7);
    float cpi8=(float)(spi1+spi2+spi3+spi4+spi5+spi6+spi7+spi8)/(float)(total_cred_1+total_cred_2+total_cred_3+total_cred_4+total_cred_5+total_cred_6+total_cred_7+total_cred_8);
    printf("sem1 %f\n", cpi1);
    printf("sem2 %f\n", cpi2);
    printf("sem3 %f\n", cpi3);
    printf("sem4 %f\n", cpi4);
    printf("sem5 %f\n", cpi5);
    printf("sem6 %f\n", cpi6);
    printf("sem7 %f\n", cpi7);
    printf("sem8 %f\n", cpi8);
    mysql_free_result(result);
    return;
}

int main() {
    

    MYSQL *conn=mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return EXIT_FAILURE;
    }

    if (mysql_real_connect(conn, "localhost", "root", NULL, "week10", 0, NULL, 0) == NULL) {
        fprintf(stderr, "Failed to connect to database: Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    printf("Connected to MySQL server with database week10\n");

    
    //6
    char roll_number[11]="180101008";
    roll_number[10]='\0';

    compute_cpi(roll_number,conn);

    mysql_close(conn);
    exit(0);

}