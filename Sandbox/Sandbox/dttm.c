#include <time.h>
#include <string.h>
#include <stdio.h>

int main (void)
{
struct tm veley, verakku, tm_1, tm_2;
char time_str1[80] = "06/12/1997 10:30:30";
char time_str2[80] = "08/12/1997 10:30:39";
char time_str3[80] = "";
char time_str4[80] = "";
time_t tm1, tm2;

strptime(time_str1, "%m/%d/%Y %T", &veley);
printf("%s",asctime(&veley));   

strptime(time_str2, "%m/%d/%Y %T", &veley);
printf("%s", asctime(&veley));   

printf("Enter the time 1 in the mm/dd/yy hh:mm format: ");
gets(time_str3); 
strptime(time_str3, "%m/%d/%y %R", &veley);
printf("Meeting start at %s or %d seconds",asctime(&veley), tm1);

printf("Enter the meeting end time hh:mm format: ");
gets(time_str4);
strptime(time_str4, "%R", &verakku);

verakku.tm_sec   = veley.tm_sec;
verakku.tm_mday  = veley.tm_mday;
verakku.tm_mon   = veley.tm_mon;
verakku.tm_year  = veley.tm_year;
verakku.tm_wday  = veley.tm_wday;
verakku.tm_yday  = veley.tm_yday;
verakku.tm_isdst = veley.tm_isdst;

/*
 * mktime() is found to alter the passed tm structure & so let's pass 
 * copies of the same saving the original for our later reference.
 */
tm_1 = veley;
tm_2 = verakku;
tm1 = mktime(&tm_1);
tm2 = mktime(&tm_2);
gmtime_r(&tm1, &tm_1);
gmtime_r(&tm2, &tm_2);
tm1 = mktime(&tm_1);
tm2 = mktime(&tm_2);

printf("Meeting lasts till %s for %f seconds", asctime(&verakku), difftime(tm2, tm1));   
}
