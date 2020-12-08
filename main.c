#include <stdio.h>
#include <string.h>
int user_index = 0, flight_index=0;
typedef struct
{
    int flight_no, ticket_price;
    char departure[50], destination[50];
} flight;

typedef struct
{
    int passport_number,flight_number,seat_no;
    char full_name[50];
} user;

void saveUser(user users[], int n)
{
    FILE* f = fopen("user_info.txt","w");
    int i;
    fprintf(f,"%s\n","Full_Name  Passport_Number  Flight_Number   Seat_Number");
    for(int  i=0; i<n; i++)
    {
        fprintf(f,"%s",users[i].full_name);
        fprintf(f,"%s"," ");

        fprintf(f,"%d",users[i].passport_number);
        fprintf(f,"%s"," ");

        fprintf(f,"%d",users[i].flight_number);
        fprintf(f,"%s"," ");

        fprintf(f,"%d\n",users[i].seat_no);
    }
    fclose(f);
}

void EnterNewUser(user u[])
{
    printf("Enter Full Name : ",user_index+1);
    scanf("%s",&u[user_index].full_name);

    printf("Enter flight_number : ",user_index+1);
    scanf("%d",&u[user_index].flight_number);

    printf("Enter passport_number : ",user_index+1);
    scanf("%d",&u[user_index].passport_number);

    printf("Enter seat_number : ",user_index+1);
    scanf("%d",&u[user_index].seat_no);
    user_index= user_index +1;
}

void saveFlights(flight flights[], int n)
{
    FILE* f = fopen("flight_info.txt","w");
    int i;
    fprintf(f,"%s\n","Flight_Number  Departure  Destination  Ticket_Price");
    for(int  i=0; i<n; i++)
    {
        fprintf(f,"%d",flights[i].flight_no);
        fprintf(f,"%s"," ");

        fprintf(f,"%s",flights[i].departure);
        fprintf(f,"%s"," ");

        fprintf(f,"%s",flights[i].destination);
        fprintf(f,"%s"," ");

        fprintf(f,"%d",flights[i].ticket_price);
        fprintf(f,"%s\n"," ");
    }
    fclose(f);
}

void EnterNewFlight(flight f[])
{
    printf("Enter Flight Number : ",flight_index+1);
    scanf("%d",&f[flight_index].flight_no);

    printf("Enter Departure : ",flight_index+1);
    scanf("%s",&f[flight_index].departure);

    printf("Enter Destination : ",flight_index+1);
    scanf("%s",&f[flight_index].destination);

    printf("Enter Ticket Price : ",flight_index+1);
    scanf("%d",&f[flight_index].ticket_price);
    flight_index= flight_index +1;
}

int printData(char filename[100])
{
    FILE * f2;
    f2 = fopen (filename, "r");
    rewind(f2);
    char str[100];
    int i=0;
    while (fgets(str, 100, f2) != NULL)
    {
        i++;
        printf("%s", str);
    }
    return i;
}

void SortFlightsBy_flightNo (flight f[],int n)
{
    int i,pass,j;
    flight s;
    for ( pass=1; pass<n; pass++)
        for ( j=0; j<n-pass; j++)
        {
            if (f[j].flight_no > f[j+1].flight_no)
            {
                s=f[j];
                f[j]=f[j+1];
                f[j+1]=s;
            }
        }
}

void SortUsersBy_Name (user x[],int n)
{
    int i,pass,j;
    user temp[1000];
    for ( pass=1; pass<n; pass++)
        for ( j=0; j<n-pass; j++)
        {
            if (strcmp(x[j].full_name,x[j+1].full_name)==1)
            {
                temp[1]=x[j];
                x[j]=x[j+1];
                x[j+1]=temp[1];
            }
        }
}

int SearchByfight_no (flight x[],int n,int fight_no)
{
    int found =0,i,j;
    for ( i=0 ; i<n; i++)
    {
        if (fight_no ==x[i].flight_no)
        {
            found=1;
            printf("Found!\n");
            return i;
        }
    }
    if (found==0)
    {
        printf("NOT Found!\n");
        return -1;
    }
}

void display_sum_avg_tickts(flight f[], int n)
{
    int sum=0;
    for(int i=0; i<n; i++)
        sum+= f[i].ticket_price;
    printf("Sum of flight Tickets = %d and Average = %f\n",sum,1.0*sum/n);
}
int main()
{
    user u[100];
    flight f[100];
    while(1)
    {
        printf("**************************************************\n");
        printf("1-Enter New User\n");
        printf("2-Enter New Flight\n");
        printf("3-Display All Users\n");
        printf("4-Display All Flights\n");
        printf("5-Sort Users\n");
        printf("6-Sort Flights\n");
        printf("7-Search for Flight\n");
        printf("8-Print Sum and Average of flight Tickets\n");
        printf("9-Exit\n");
        printf("**************************************************\n");

        int choice;
        printf("Your Choice: ");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            EnterNewUser(u);
            saveUser(u,user_index);
            break;
        case 2:
            EnterNewFlight(f);
            saveFlights(f,flight_index);
            break;

        case 3:
            user_index = printData("user_info.txt");
            break;

        case 4:
            flight_index = printData("flight_info.txt");
            break;

        case 5:
            if(user_index==0)
            {
                printf("No Data Found\n");
                break;
            }

            SortUsersBy_Name(u,user_index);
            saveUser(u,user_index);
            printf("---------------------------------------------\n");
            printf("Sort Successfully\n");
            printf("---------------------------------------------\n");
            break;

        case 6:
            if(flight_index==0)
            {
                printf("No Data Found\n");
                break;
            }
            SortFlightsBy_flightNo(f,flight_index);
            saveFlights(f,flight_index);
            printf("---------------------------------------------\n");
            printf("Sort Successfully\n");
            printf("---------------------------------------------\n");
            break;

        case 7:
            if(flight_index==0)
            {
                printf("No Data Found\n");
                break;
            }
            int flight_no;
            printf("Enter flight_no You Search\n");
            scanf("%d", &flight_no);
            int index = SearchByfight_no(f,flight_index,flight_no);
            if(index!= -1)
            {
                printf("---------------------------------------------\n");
                printf("%d\t%s\t%s\t%d\n",f[index].flight_no,f[index].departure,
                       f[index].destination,f[index].ticket_price);
                printf("---------------------------------------------\n");
            }
            break;

        case 8:
            display_sum_avg_tickts(f,flight_index);
            break;
        case 9:
            exit(0);
        default:
            printf("Error Choice\n");
        }
    }
}
