#include <simplecpp>
#include <iostream>
#include <fstream>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

/* reads from keypress, doesn't echo */
int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

/* //reads from keypress, echoes 
int getche(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}*/

char a[11] = {0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0};//array to note down the characters of the file name.

class student//making class of student
{
	public:	
	string rl;
	float marks;
	string grade;
	student(){rl="0";marks=0.0;grade="nil";}//constructor
};

student maxmarks(student a[],int num_stu)// function to find maximum marks
{
	student tmp;
	for(int i=0;i<num_stu;i++)
	{
		if(a[i].marks>tmp.marks){tmp.rl=a[i].rl;tmp.marks=a[i].marks;}
	}
	return tmp;	

}

float mean(student a[],int num_stu)//function to find mean of marks 
{	
	float tmp=0;
	for(int i=0;i<num_stu;i++)		
	{
		tmp+=a[i].marks;
	}
	return tmp/num_stu;
}

float sd(student a[], int num_stu)//function to find standard deviation
{
	float tmp=0;
	for( int i=0;i<num_stu;i++)
	{
		tmp+=a[i].marks*a[i].marks;
	}
	
	float y=mean(a,num_stu);
	tmp=tmp/num_stu;
	
	return sqrt(tmp-y*y);
}

void histo_pie(student a[],int num_stua,float ox,float oy,float widx,float widy,float CVL,string sub,string xa,string xb,string xc)// function for making histogram and pie chart.
{
	//histogram and pie chart.
	{//histogram	
	student st=maxmarks(a,num_stua);
	float max_marks=st.marks;
	int nx=10,mark[nx],max=0;//nx is the number of divisions on x axis;mark array store the number of student belonging to a particular interval.
	for(int i=0;i<nx;i++)//creating array mark.
		{
			int count=0;
			for(int i1=0;i1<num_stua && i!=nx-1;i1++)
				{
					if(a[i1].marks>=(max_marks/nx)*i && a[i1].marks<max_marks*(i+1)/nx){count++;};
				}
			if(i==nx-1)
				{
					for(int i1=0;i1<num_stua;i1++)
					{
						if(a[i1].marks>=(max_marks/nx)*i && a[i1].marks<=max_marks*(i+1)/nx){count++;};
					}
				}
			mark[i]=count;
			if(count > max)max=count;// getting max number of students having marks in a given range.
		}	
	
	
	int i=0,ny=max;//ny is the number of divisions on y axis which is around the max. 
	float dx=(widx/nx),dy=(widy/ny);//dx and dy are units on x and y axis.
	Line yl[ny+2],xl[101],hist[20];Text yt[ny+2],xt[101];//Lines and texts.
	Line xaxis(ox,CVL-oy,ox+widx*(1.1),CVL-oy); xaxis.imprint();//x axis
	Text xaxistag(ox+widx*(0.6),CVL-oy+40,"Marks of students");xaxistag.imprint();
	Line yaxis(ox,CVL-oy,ox,CVL-oy-widy*(1.1)); yaxis.imprint();//y axis
	Text yaxistag1(ox-50,CVL-oy-widy*(0.5)-30,"Number");yaxistag1.imprint();
	Text yaxistag2(ox-50,CVL-oy-widy*(0.5),"of");yaxistag2.imprint();
	Text yaxistag3(ox-50,CVL-oy-widy*(0.5)+30,"students");yaxistag3.imprint();
	Line xarrow1(ox,CVL-oy-widy*(1.1),ox+5,CVL-oy-widy*(1.1)+10);xarrow1.imprint();//arrows at end of axis
	Line xarrow2(ox,CVL-oy-widy*(1.1),ox-5,CVL-oy-widy*(1.1)+10);xarrow2.imprint();
	Line yarrow1(ox+widx*(1.1),CVL-oy,ox+widx*(1.1)-10,CVL-oy+5);yarrow1.imprint();
	Line yarrow2(ox+widx*(1.1),CVL-oy,ox+widx*(1.1)-10,CVL-oy-5);yarrow2.imprint();
	repeat(ny/5+1)//divisions on y axis
	{
		yl[i].reset(ox-10 , CVL-oy - (i) * dy*5 , ox , CVL-oy - (i) * dy*5);yl[i].imprint();
		yt[i].reset(ox-15 , CVL-oy - (i) * dy*5 ,(i)*5);yt[i].imprint() ;
		i++ ;
	}
	i=0;
	repeat(nx+1)//divisions on x axis
	{
		xl[i].reset(ox+(i)*dx,CVL-oy,ox+(i)*dx,CVL-oy+10);xl[i].imprint();
		xt[i].reset(ox+(i)*dx,CVL-oy+20,(i*max_marks/nx));xt[i].imprint();
		i++;
	}
	i=0;
	int px=ox+(dx/2),py=CVL-oy;// drawing histogram
	Line hist1(ox,CVL-oy,px,py-mark[i]*dy);hist1.setColor(COLOR(0,0,255));hist1.imprint();
	repeat(nx-1)
	{	
		hist[i].reset(px+(i)*dx,py-mark[i]*dy,px+(i+1)*dx,py-mark[i+1]*dy);hist[i].setColor(COLOR(0,0,255));hist[i].imprint();
		i++;
	}	
	Line hist2(px+(i)*dx,py-mark[i]*dy,px+(i+1)*dx,CVL-oy);hist2.setColor(COLOR(0,0,255));hist2.imprint();//histogram ended.
	Text heading(ox + widx*(0.5)-100,CVL-oy-widy-10,"Performance in exam ");heading.imprint();//heading
	Text heading1(ox + widx*(0.5)-10,CVL-oy-widy-10,sub);heading1.setColor(COLOR(255,0,0));heading1.imprint();
	Text heading2(ox + widx*(0.5)+30,CVL-oy-widy-10,"year");heading2.setColor(COLOR(0,255,0));heading2.imprint();
	Text heading21(ox + widx*(0.5)+60,CVL-oy-widy-10,xa);heading21.setColor(COLOR(0,255,0));heading21.imprint();
	Text heading3(ox + widx*(0.5)+100,CVL-oy-widy-10,"sem");heading3.setColor(COLOR(0,0,255));heading3.imprint();
	Text heading31(ox + widx*(0.5)+120,CVL-oy-widy-10,xb);heading31.setColor(COLOR(0,0,255));heading31.imprint();
	Text heading4(ox + widx*(0.5)+140,CVL-oy-widy-10,"exam");heading4.setColor(COLOR(255,0,80));heading4.imprint();
	Text heading41(ox + widx*(0.5)+160,CVL-oy-widy-10,xc);heading41.setColor(COLOR(255,80,0));heading41.imprint();
	
	Text stddev(ox+widx*(1.2),CVL-oy-widy-30,"Standard Deviation is ");stddev.imprint();//showing std. Deviation
	Text stddevt(ox+widx*(1.2)+150,CVL-oy-widy-30,sd(a,num_stua));stddevt.imprint();
	Text mean1(ox+widx*(1.2),CVL-oy-widy-15,"Mean is ");mean1.imprint();//Mean
	Text mean2(ox+widx*(1.2)+150,CVL-oy-widy-15,mean(a,num_stua));mean2.imprint();
	Text highest(ox+widx*(1.2),CVL-oy-widy,"Highest mark in the exam");highest.imprint();//highest marks
	Text high_name(ox+widx*(1.2)+150,CVL-oy-widy,st.marks);high_name.imprint();
	}
	{// pie chart.
	float r=widy*(0.2);//radius
	ox =ox+(1.4)*widx; oy =oy + (0.5)*widy;//origin of circle
	Circle circle(ox,CVL-oy,r);
	circle.imprint();
	student st=maxmarks(a,num_stua);
	float max_marks=st.marks;
	int div=5,mark[div],max=0;//div is the number of divisions in pie chart, max 9 divsions allowed.
	for(int i=0;i<div;i++)//entering data in mark[] array of pie chart
		{
			int count=0;
			for(int i1=0;i1<num_stua;i1++)
				{
					if(a[i1].marks>=(max_marks/div)*i && a[i1].marks<max_marks*(i+1)/div){count++;};
				}
			mark[i]=count;
			if(count > max)max=count;// getting max number of students having marks in a given range.
		}	
	int p=0,i=0;
	repeat(div){p=p+mark[i];i++;}
	i=0;		
	Line l[div][2*max],llabel[div];Text label[div][3];//creating pie chart
	float angle=0;
	i=0;int i1=0;
	int a1[9]={255,0,0,0,255,60,130,250,255},b1[9]={0,255,0,135,255,255,0,0,255},c1[9]={0,0,255,135,0,140,255,180,255};//creating colors for pie chart.		
	repeat(div)//drawing lines for coloring pie chart.
		{		
				repeat(2*mark[i1]){ l[i1][i].reset(ox,CVL-oy,ox+r*(cosine(((float)i/p)*360/2+angle)),CVL-oy-r*(sine(((float)i/p)*360/2+angle)));l[i1][i].setColor(COLOR(a1[i1],b1[i1],c1[i1]));l[i1][i].imprint();
				i++;}i=i/2;
				llabel[i1].reset(ox+r*(cosine(((float)i/p)*360/2+angle)),CVL-oy-r*(sine(((float)i/p)*360/2+angle)),ox+(r+20)*(cosine(((float)i/p)*360/2+angle)),CVL-oy-(r+20)*(sine(((float)i/p)*360/2+angle)));llabel[i1].setColor(COLOR(a1[i1],b1[i1],c1[i1]));llabel[i1].imprint();
				label[i1][0].reset(ox+(r+35)*(cosine(((float)i/p)*360/2+angle))-20,CVL-oy-(r+35)*(sine(((float)i/p)*360/2+angle)),(float)max_marks*((float)i1/div));
				label[i1][0].setColor(COLOR(a1[i1],b1[i1],c1[i1]));label[i1][0].imprint();
				label[i1][1].reset(ox+(r+35)*(cosine(((float)i/p)*360/2+angle)),   CVL-oy-(r+35)*(sine(((float)i/p)*360/2+angle)),"-");
				label[i1][1].setColor(COLOR(a1[i1],b1[i1],c1[i1]));label[i1][1].imprint();
				label[i1][2].reset(ox+(r+35)*(cosine(((float)i/p)*360/2+angle))+20,CVL-oy-(r+35)*(sine(((float)i/p)*360/2+angle)),(float)max_marks*((float)(i1+1)/div));
				label[i1][2].setColor(COLOR(a1[i1],b1[i1],c1[i1]));label[i1][2].imprint();
				angle=angle+(((float)i)/p)*360;
				i1++;i=0;
		}
	}
	wait(10);
}	

void histo_pie1(student a[],int num_stua,string sub,string xa,string xb,string xc)//for drawing one histogram.
{	
	float widy=400,widx =700,ox=90,oy=60;
	float CVL=(1.4)*widy,CHL=2*widx;
	initCanvas("Performance of Class",CHL,CVL);
	histo_pie(a,num_stua,ox,oy,widx,widy,CVL,sub,xa,xb,xc);
}

void histo_pie2(student a[],int num_stua,student b[],int num_stub,string sub,string xa,string xb,string xc,string xd)//for two histograms.
{
	float widy=250,widx=600,ox=90,oy=60;
	float CVL=(2.8)*widy,CHL=(2)*(widx);
	initCanvas("Performance of Class",CHL,CVL);
	histo_pie(a,num_stua,ox,oy,widx,widy,CVL,sub,xa,xb," ");
	histo_pie(b,num_stub,ox,oy+(1.3)*widy,widx,widy,CVL,sub,xc,xd," ");
}		

void grade(student a[],int num_stu,int perf[])// function to change the grades
{	
	student st= maxmarks(a,num_stu);
	float max_marks=st.marks;
	for(int i=0;i<13;i++){perf[i]=0;}
	float markAP,mark[11];
	cout<<"\t \t \t \t \t Welcome to grading panel \n";
	cout<<"\t \t\t What criteria do you want for grading the students\n";//Getting the lower limit of grading.
gAP:cout<<"Minimmum marks for student  getting AP grade.\t\t";
	cin>>markAP;if(markAP>max_marks){cerr<<"Invalid marks\tagain give marks.";goto gAP;}
g:	cout<<"Minimmum marks for student getting 10 grade points.\t\t";
	cin>>mark[10];if(mark[10]>=markAP||mark[10]<0){cerr<<"Invalid marks\tagain give marks.\n";goto g;}
	for(int i=9;i>=4;i--)
	{	
		g1:
		cout<<"Minimmum marks for student getting "<<i<<" grade points.\t\t";
		cin>>mark[i];if(mark[i]>=mark[i+1]||mark[i]<0){cerr<<"Invalid marks\tagain give marks.\n";goto g1;}
	}
	for(int i=0;i<num_stu;i++)//giving grades and counting number of students.
	{
		if(a[i].marks<=max_marks && a[i].marks>=markAP){a[i].grade="AP";perf[11]++;}
		else if(a[i].marks<markAP && a[i].marks>=mark[10]){a[i].grade="10";perf[10]++;}
		else if(a[i].marks<mark[10] && a[i].marks>=mark[9]){a[i].grade="9";perf[9]++;}
		else if(a[i].marks<mark[9] && a[i].marks>=mark[8]){a[i].grade="8";perf[8]++;}
		else if(a[i].marks<mark[8] && a[i].marks>=mark[7]){a[i].grade="7";perf[7]++;}
		else if(a[i].marks<mark[7] && a[i].marks>=mark[6]){a[i].grade="6";perf[6]++;}
		else if(a[i].marks<mark[6] && a[i].marks>=mark[5]){a[i].grade="5";perf[5]++;}
		else if(a[i].marks<mark[5] && a[i].marks>=mark[4]){a[i].grade="4";perf[4]++;}	
		if(a[i].marks<mark[4] && a[i].marks>=0){a[i].grade="Fail";perf[0]++;}
	}	
}

string encryption(string s)//function for encryption
{
	string a=s;
	int y=((s.length()+3)*37)%17;//creating new variable y which is related to length of string.
	for(int c=0;c<s.length();c++)//avoiding encryption of enter and space command
	{	if(s[c]==13||s[c]==32){a[c]=s[c];}
     else {
	int b=0;//encrypting the string using ASCII Code
	b=s[c]+y;
	if(b>126){b=b-94;}
	if(b<33){b=b+94;}
	a[c]=b;}};
	return a;}

string decryption(string s)//function for decryption
{
	string a=s;
	int y=((s.length()+3)*37)%17;
	for(int c=0;c<s.length();c++)
	{if(s[c]==13||s[c]==32){a[c]=s[c];}
     else {
	int b;//reverse of encryption.
	b=s[c]-y;
	if(b>126)
	{b=b-94;}
	if(b<33)
	{b=b+94;}
	a[c]=b;}}
	return a;};

void listing(student a[],int num_stu,int perf[])// function to list the details of students.
{	
	ofstream coutt("grading",ios::out);
	coutt<<"t\t\t\t\tMarks of all the students"<<endl;
	coutt<<"roll  no.l\t\t\tMarks\t\t\tGrade\n\n";
	for(int i=0;i<num_stu;i++)
	{
		coutt<<decryption(a[i].rl)<<"\t\t\t"<<a[i].marks<<"\t\t\t"<<a[i].grade<<endl;
	}	
	coutt<<"No. of students having AP grade is : "<<perf[11]<<endl;
	for(int i=4;i<=10;i++)
	{
		coutt<<"No. of students having " <<i<<" grade points is : "<<perf[i]<<endl;
	}	
	coutt<<"No. of students getting FR : "<<perf[0]<<endl;
}

void  stoc(string s)//converting string to array of character.
{
	for(int y=0;y<s.length();y++)
	{a[y]=s[y];};
	return ;
};

class pass1
{
	public:
	string use;
	string pas;
};	       
	
main_program
{	
	int perf[13];
	int ia=0, ib=4, i=0,inp=0,inpi=0,iy=0,iu=0;
	string user,pass,sub,f1,sa,sb,sc,s,si,sd,se,sf,sg,sh,sk,sl,saa,sy,sr,sn,jk,hk,xa,xb,xc,xd; //creating strings which will be used later in program.
	char im;
    pass="hereasdd";
	char ca,ch;
	cout<<"\t\tPress 1 for accessing as PROF\n \t\tPress 2  for accessing as JTA "<<endl;//checking the user is JTA or PROF or ADMIN
	cin>>ca;
	if(ca=='1')//if user is prof
		{
			cout<<"your subject (please type in small letters) "<<endl;
			cin>>sub;
			cout<<"enter your user name"<<endl;//checking user name and password
			cin>>user;	
			cout<<"enter your password(only letter number and special char allowed)"<<endl;
			getch();
			while(1)
				{
					ch=getch();
					if(ch=='\n' || ia==8) break;
					pass[ia]=ch;
					ia++;
					cout<<"*";
				}	
			f1=sub+"p00001";
			stoc(f1);
			ifstream in(a,ios::in);
			while(in>>sa)//getting encryted user name and passwords from password file, decrypting it and then comparing. 
				{
					if(sa==encryption(user))
						{
							in>>sb;
							if(sb==encryption(pass)){ib=1;} 
							else {ib=5; break;} 
							break;
						}
					else{in>>sb; ib=4;}
				}
		}
	else if(ca=='2')//if user is JTA.
		{
			cout<<"Your subject (please type in small letters) "<<endl;
			cin>>sub;
			cout<<"Enter your user name"<<endl;
			cin>>user;	
			cout<<"Enter your password(only letter number and special char allowed) No backspace allowed"<<endl;
			getch();
			while(1)
				{
					ch=getch();
					if(ch=='\n' || ia==8) break;
					pass[ia]=ch;
					ia++;
					cout<<"*";
				}	
			f1=sub+"p00002";
			stoc(f1);
			ifstream in(a,ios::in);
			while(in>>sa)
				{
					if(sa==encryption(user))//checking password and user id.
						{
							in>>sb;
							if(sb==encryption(pass)){ib=2;} 
							else {ib=5; break;} 
							break;
						}
					else{in>>sb; ib=4;}
				}
		}
	else if(ca=='3')//if user is ADMIN.
		{
			getch();//ADMIN have to type special character to enter its profile.
			while(1)//Password present only in program file, no extra file for storing password of admin. 
				{
					ch=getch();
					if(ch=='\n' || ia==20) break;
					pass[ia]=ch;
					ia++;
					cout<<"*";
				}	
			if(pass=="sohamsid")
				{
					ib=3;
				}
		}// value is stored in ib integer
	if (ib==1)//Prof.
		{
my:   		inpi=0;
			cout<<"\t\tWelcome Professor \n\t\tPleased to have you on program \n\n\t\tPress 'u' to see updates from JTA \n\t\tPress 'm' for changing marks\n\t\tPress 'h' for seeing Histogram and statistics  of marks\n\t\tPress 'l' for getting a list of marks\n\t\tPress 'a' for adding a list of marks\n\t\tPress 'g' for giving the grades\n(You can anytime press 'q' to go back in entire program"<<endl;
			while(cin>>ch)
			{
				if(ch=='q')//going back
					{
						goto man;
					}
				if(ch=='l')//listing the details of students
					{
						cout<<" Enter the year as **** (eg. - '2013') ,then Press Enter.\nEnter the Semester as '1' or '2' , then Press Enter\nEnter the number of exam as '1' or '2' or ...., then Press enter\n( Press 'q' to go back.) " <<endl;
						cin>>sa;
						if (sa=="q"){goto my5;}
						cin>>sb>>sc;
						sa=sub+sa+sb+sc;
						stoc(sa);
						ifstream in1(a,ios::in);
						ifstream inia(a,ios::in);
						ia=0;
						while(getline(in1,sb)){ia++;};
						student mb[ia];
						for( ib=0;ib<ia;ib++)
							{
								inia>>mb[ib].rl>>mb[ib].marks;
							}
						for( ib=0;ib<ia;ib++)
							{
								mb[ib].rl=decryption(mb[ib].rl);
							};
						ofstream outa("Hello",ios::out); 
						for( ib=0;ib<ia;ib++)
							{
								outa<<mb[ib].rl<<"  "<<mb[ib].marks<<endl;
							}		
						cout<<"your text has been sent to file named 'Hello' please rename it before using it again"<<endl;
						goto my;
					};
				if(ch=='u')//to see updates from JTA
					{
						sa=sub+"update";
						stoc(sa);
						ifstream in1(a,ios::in);//a is the name of file.(a is a character array.)
						cout<<"Which No. of update you want to see ? "<<endl;
						cin>>ia;ib=0;inpi=0;
						while(ib<ia && getline(in1,sa,'-')&&getline(in1,hk,':')&&getline(in1,jk))
							{
								if((ia-ib)==1)
									{
										cout<<decryption(sa)<<" - "<<hk<<" : "<<decryption(jk)<<endl;ib++;inpi=2;break;
									}
									ib++;
							};
						cout<<endl;	
						if(inpi!=2)
							{
								cout<<"No Update to display"<<endl;
							}
						goto my;
					}
				if(ch=='a')//to add marks.
aka:				{
						cout<<"Please enter the file name from which you want to enter the marks. ( NOTE : File name should be of 11 letters . eg. ma105batch1 )"<<endl;//asking for file name ,11 letters is essential because it has to be used in ifstream, which required some manipuation//see stoc function and 'a[]' array.
						cin>>sy;
						if(sy=="q")goto my;
						if(sy.length()!=11)goto aka;//file name should not exceed 11 letters.
						stoc(sy); 
						ifstream in1(a,ios::in);
						ifstream inia(a,ios::in);
						ia=0;
						while(getline(in1,sb))
						ia++;
						student ma[ia];
						for(ib=0;ib<ia;ib++)
							{
								inia>>ma[ib].rl>>ma[ib].marks;
							}
						for( ib=0;ib<ia;ib++)//encrypting the roll numbers.
							{
								ma[ib].rl=encryption(ma[ib].rl);
							}
						cout<<"Enter the details of the exam \nEnter year as **** (eg. 2013). Press Enter.\nSemester as '1' or '2' .Press Enter. \nEnter the No. of Exam as '1','2',...." <<endl;//getting details of exam.
						cin>>sa;
						if (sa=="q"){goto my;}
						cin>>sb>>sc;
						sa=sub+sa+sb+sc;
						stoc(sa);
						ofstream outa2(a,ios::out);
						for( ib=0;ib<ia;ib++)//marks stored in a file in encrypted format.
							{
								outa2<<ma[ib].rl<<"  "<<ma[ib].marks<<endl;
							}
						goto my;
					} 
				if(ch=='m')//for changing marks of student.
my1: 				{
						cout<<"Enter the year as **** (eg. - '2013') ,then Press Enter.\nEnter the Semester as '1' or '2' , then Press Enter\nEnter the number of exam as '1' or '2' or ...., then Press enter "<<endl;
						cin>>sa;
						if (sa=="q"){goto my;}
						cin>>sb>>sc;
						sa=sub+sa+sb+sc;
						sr=sa;
						stoc(sa);
						ifstream in1(a,ios::in);
						ifstream inia(a,ios::in);
						ia=0;
						while(getline(in1,sb))ia++;
						student m[ia];
						for( ib=0;ib<ia;ib++)
							{
								inia>>m[ib].rl>>m[ib].marks;
							};
my2: 					cout<<"Enter the roll no. of student (if you have completed all edits, press 'q')"<<endl;
						while(cin>>s)
							{
								if(s=="q")//if a user exits, then the marks got changed in file
									{	
										stoc(sr);  
										ofstream out1(a,ios::out);
										for( ib=0;ib<ia;ib++)
											{	
												out1<<m[ib].rl<<" "<<m[ib].marks<<endl;
											} 
										goto my1;
									}
								for(ib=0;ib<ia;ib++)
									{
										if(m[ib].rl==encryption(s))//searching roll number in encrypted format.
											{
												cout<<"enter your changed marks " <<endl;
												cin>>m[ib].marks;
												s=sub+"change";
												stoc(s);
												ofstream ou2(a,ios::app);
												ou2<<"Marks of student having roll No. "<<m[ib].rl<<" has been changed to "<<m[ib].marks<<" by Prof. "<<user<<endl; 
												ib=ia; 
												goto my2;
											}
									};
								cout<<"Please enter a correct roll no. or check if file for the subject exist "<<endl;
								goto my2;
							}
					}
				if(ch=='g')//for grading.
					{
						cout<<"Enter the year as **** . Press Enter. \nSemester as '1' or 2 . Press enter." <<endl;
						cin>>sa;
						if (sa=="q"){goto my;}
						cin>>sb;
						sa=sub+sa+sb;
						ia=0;ib=0;
						sn=sa+"1";//creating ifstream for counting total number of students of a paricular sem of a particular year.
						stoc(sn);
						ifstream inopm(a,ios::in);
						while(getline(inopm,sb))
						{ia++;};
						student m[ia];
						sn=sa+"1";//creating ifstreams of all the files of all exams of a same semester.
						stoc(sn);
						ifstream in1(a,ios::in);
						ib=0;
						while(in1>>m[ib].rl>>m[ib].marks && ib<ia)//adding marks of all exam of students in array m[].
							{sn=sa+"2";
							stoc(sn);
							ifstream in2(a,ios::in); 
							sn=sa+"3";
							stoc(sn);
							ifstream in3(a,ios::in);
							sn=sa+"4";
							stoc(sn);
							ifstream in4(a,ios::in);
							sn=sa+"5";
							stoc(sn);
							ifstream in5(a,ios::in);
							sn=sa+"6";
							stoc(sn);
							ifstream in6(a,ios::in);
							sn=sa+"7";
							stoc(sn);
							ifstream in7(a,ios::in);
							sn=sa+"8";
							stoc(sn);
							ifstream in8(a,ios::in);
							sn=sa+"9";
							stoc(sn);
							ifstream in9(a,ios::in);
								while(in2>>si)
									{
										if(si==m[ib].rl)
											{
												in2>>i;m[ib].marks=m[ib].marks+i;
												while(in3>>si)
													{
														if(si==m[ib].rl)
															{
																in3>>i;m[ib].marks=m[ib].marks+i;
																while(in4>>si)
																	{
																		if(si==m[ib].rl)
																			{
																				in4>>i;m[ib].marks=m[ib].marks+i;
																				while(in5>>si)
																					{
																						if(si==m[ib].rl)
																							{
																								in5>>i;m[ib].marks=m[ib].marks+i;
																								while(in6>>si)
																									{
																										if(si==m[ib].rl)
																											{
																												in6>>i;m[ib].marks=m[ib].marks+i;
																												while(in7>>si)
																													{
																														if(si==m[ib].rl)
																															{
																																in7>>i;m[ib].marks=m[ib].marks+i;
																																while(in8>>si)
																																	{
																																		if(si==m[ib].rl)
																																			{
																																				in8>>i;m[ib].marks=m[ib].marks+i;
																																				while(in9>>si)
																																					{
																																						if(si==m[ib].rl)
																																							{
																																								in9>>i;m[ib].marks=m[ib].marks+i;
																																							}
																																					}
																																			}
																																	}
																															}
																													}
																											}
																									}
																							}
																					}
																			}
																	}
															}
													}
											}
									}
								ib++;	
							}//addition done :).
						grade(m,ib,perf);
						listing(m,ib,perf);
						cout<<"your data with grades has been sent to file named grading please rename it"<<endl;
					};
				if(ch=='h')//for making histogram and statistics.
					{
ggg: 					cout<<"For watching 1 Histogram Press '1' \nFor watching 2 Histograms for comparison Press '2'"<<endl;
						cin>>im;
						if(im=='q')goto my;
						if(im!='1'&&im!='2')goto ggg;
						if(im=='1')//for drawing only one histogram .
							{
								cout<<"Press '1' for watching histogram of only one particular Exam.\nPress '2' for watching combined histogram of all exams "<<endl;
								cin>>ch;
								if(ch=='1')
									{
										cout<<"Enter the details of the exam \nEnter year as **** (eg. 2013). Press Enter.\nSemester as '1' or '2' .Press Enter. \nEnter the No. of Exam as '1','2',...."<<endl;
										cin>>sa;
										if (sa=="q"){goto my;}
										cin>>sb>>sc;
										xa=sa;xb=sb;xc=sc;
										sa=sub+sa+sb+sc;
										stoc(sa);
										ifstream in1(a,ios::in);
										ifstream inax(a,ios::in);
										ia=0;
										while(getline(inax,sb))
										{ia++;};
										student m[ia];
										for(ib=0;ib<ia;ib++)
											{
													in1>>m[ib].rl>>m[ib].marks;
											};
										for( ib=0;ib<ia;ib++)
											{	
												m[ib].rl=decryption(m[ib].rl);
											};//m[] is the array of students of that particular exam.
										histo_pie1(m,ib,sub,xa,xb,xc);
										goto my;
									};
								if(ch=='2')
									{
										cout<<"Enter the details of the exam \nEnter year as **** (eg. 2013). Press Enter.\nSemester as '1' or '2' .Press Enter.\t(Press 'q' for exit)" <<endl;
										cin>>sa;
										if (sa=="q"){goto my;}
										cin>>sb;
										xa=sa;xb=sb;
										sa=sub+sa+sb;
										ia=0;ib=0;
										sn=sa+"1";//creating ifstream for counting number of student of exam.
										stoc(sn);
										ifstream inopm(a,ios::in);
										while(getline(inopm,sb))
										{ia++;};
										student m[ia];
										sn=sa+"1";//creating ifstreams for all the different files of particular subject and semesters.
										stoc(sn);
										ifstream in1(a,ios::in);
										ib=0;
										while(in1>>m[ib].rl>>m[ib].marks && ib<ia)//adding all the marks of same student in array m[].
											{sn=sa+"2";
										stoc(sn);
										ifstream in2(a,ios::in);
										sn=sa+"3";
										stoc(sn);
										ifstream in3(a,ios::in);
										sn=sa+"4";
										stoc(sn);
										ifstream in4(a,ios::in);
										sn=sa+"5";
										stoc(sn);
										ifstream in5(a,ios::in);
										sn=sa+"6";
										stoc(sn);
										ifstream in6(a,ios::in);
										s=sa+"7";
										stoc(sn);
										ifstream in7(a,ios::in);
										sn=sa+"8";
										stoc(sn);
										ifstream in8(a,ios::in);
										sn=sa+"9";
										stoc(sn);
										ifstream in9(a,ios::in);
										
												while(in2>>si)
													{
														if(si==m[ib].rl)
															{
																in2>>i;m[ib].marks=m[ib].marks+i;
																while(in3>>si)
																	{
																		if(si==m[ib].rl)
																			{
																				in3>>i;m[ib].marks=m[ib].marks+i;
																				while(in4>>si)
																					{
																						if(si==m[ib].rl)
																							{
																								in4>>i;m[ib].marks=m[ib].marks+i;
																								while(in5>>si)
																									{
																										if(si==m[ib].rl)
																											{
																												in5>>i;m[ib].marks=m[ib].marks+i;
																												while(in6>>si)
																													{
																														if(si==m[ib].rl)
																															{
																																in6>>i;m[ib].marks=m[ib].marks+i;
																																while(in7>>si)
																																	{
																																		if(si==m[ib].rl)
																																			{
																																				in7>>i;m[ib].marks=m[ib].marks+i;
																																				while(in8>>si)
																																					{
																																						if(si==m[ib].rl)
																																							{
																																								in8>>i;m[ib].marks=m[ib].marks+i;
																																								while(in9>>si)
																																									{
																																										if(si==m[ib].rl)
																																											{
																																												in9>>i;m[ib].marks=m[ib].marks+i;
																																											}
																																									}
																																							}
																																					}
																																			}
																																	}
																															}
																													}
																											}
																									}
																							}
																					}
																			}
																	}
															}
													}
												ib++;	
											}//addition done :) .
										histo_pie1(m,ib,sub,xa,xb," ");
									};
							};
						if(im=='2')//for making two histograms.
							{
								cout<<"Enter the year for First Histogram as **** .Press enter.\t Enter the Semester for the first Histogram as '1' or '2'.Press Enter.\nEnter the year for Second histogram as **** .Press enter.\t Enter the Semester for the Second Histogram as '1' or '2'.Press Enter."<<endl;
								cin>>sa;
								if (sa=="q"){goto my;}
								cin>>sb;
								xa=sa;xb=sb;
								sa=sub+sa+sb;
								sn=sa+"1";
								stoc(sn);
								ifstream inopm(a,ios::in);
								while(getline(inopm,sb))
								{ia++;};
								student m[ia];
								sn=sa+"1";//creating ifstreams.
								stoc(sn);
								ifstream in1(a,ios::in);
								ib=0;
								while(in1>>m[ib].rl>>m[ib].marks&&ib<ia)//adding all the marks of a student.
										{sn=sa+"2";
								stoc(sn);
								ifstream in2(a,ios::in);
								sn=sa+"3";
								stoc(sn);
								ifstream in3(a,ios::in);
								sn=sa+"4";
								stoc(sn);
								ifstream in4(a,ios::in);
								sn=sa+"5";
								stoc(sn);
								ifstream in5(a,ios::in);
								sn=sa+"6";
								stoc(sn);
								ifstream in6(a,ios::in);
								sn=sa+"7";
								stoc(sn);
								ifstream in7(a,ios::in);
								sn=sa+"8";
								stoc(sn);
								ifstream in8(a,ios::in);
								sn=sa+"9";
								stoc(sn);
								ifstream in9(a,ios::in);
											while(in2>>si)
												{
													if(si==m[ib].rl)
														{
															in2>>i;m[ib].marks=m[ib].marks+i;
															while(in3>>si)
																{
																	if(si==m[ib].rl)
																		{
																			in3>>i;m[ib].marks=m[ib].marks+i;
																			while(in4>>si)
																				{
																					if(si==m[ib].rl)
																						{
																							in4>>i;m[ib].marks=m[ib].marks+i;
																							while(in5>>si)
																								{
																									if(si==m[ib].rl)
																										{
																											in5>>i;m[ib].marks=m[ib].marks+i;
																											while(in6>>si)
																												{
																													if(si==m[ib].rl)
																														{
																															in6>>i;m[ib].marks=m[ib].marks+i;while(in7>>si)
																																{
																																	if(si==m[ib].rl)
																																		{
																																			in7>>i;m[ib].marks=m[ib].marks+i;
																																			while(in8>>si)
																																				{
																																					if(si==m[ib].rl)
																																						{
																																							in8>>i;m[ib].marks=m[ib].marks+i;
																																							while(in9>>si)
																																								{
																																									if(si==m[ib].rl)
																																										{
																																											in9>>i;m[ib].marks=m[ib].marks+i;
																																										}
																																								}
																																						}
																																				}
																																		}
																																}
																														}
																												}
																										}
																								}
																						}
																				}
																		}
																}
														}
												}
											ib++;	
										}//addition done :) 
								cin>>sa;
								if (sa=="q"){goto my;}
								cin>>sb;
								xc=sa;xd=sb;
								sa=sub+sa+sb;
								iy=0;iu=0;
								sn=sa+"1";
								stoc(sn);
								ifstream inopm1(a,ios::in);
								while(getline(inopm1,sb))
								{iy++;};
								student mt[ia];
								sn=sa+"1";//creating different ifstreams.
								stoc(sn);
								ifstream int1(a,ios::in);
								iu=0;
								while(int1>>mt[iu].rl>>mt[iu].marks&&iu<iy)//adding all marks of a student.
									{sn=sa+"2";
								stoc(sn);
								ifstream int2(a,ios::in);
								sn=sa+"3";
								stoc(sn);
								ifstream int3(a,ios::in);
								sn=sa+"4";
								stoc(sn);
								ifstream int4(a,ios::in);
								sn=sa+"5";
								stoc(sn);
								ifstream int5(a,ios::in);
								sn=sa+"6";
								stoc(sn);
								ifstream int6(a,ios::in);
								sn=sa+"7";
								stoc(sn);
								ifstream int7(a,ios::in);
								sn=sa+"8";
								stoc(sn);
								ifstream int8(a,ios::in);
								sn=sa+"9";
								stoc(sn);
								ifstream int9(a,ios::in);
										while(int2>>si)
											{
												if(si==mt[iu].rl)
													{
														int2>>i;mt[iu].marks=mt[iu].marks+i;
														while(int3>>si)
															{
																if(si==mt[iu].rl)
																	{
																		int3>>i;mt[iu].marks=mt[iu].marks+i;
																		while(int4>>si)
																			{
																				if(si==mt[iu].rl)
																					{
																						int4>>i;mt[iu].marks=mt[iu].marks+i;
																						while(int5>>si)
																							{
																								if(si==mt[iu].rl)
																									{
																										int5>>i;mt[iu].marks=mt[iu].marks+i;
																										while(int6>>si)
																											{
																												if(si==mt[iu].rl)
																													{
																														int6>>i;mt[iu].marks=mt[iu].marks+i;
																														while(int7>>si)
																															{
																																if(si==mt[iu].rl)
																																	{
																																		int7>>i;mt[iu].marks=mt[iu].marks+i;
																																		while(int8>>si)
																																			{
																																				if(si==mt[iu].rl)
																																					{
																																						int8>>i;mt[iu].marks=mt[iu].marks+i;
																																						while(int9>>si)
																																							{
																																								if(si==mt[iu].rl)
																																									{
																																										int9>>i;mt[iu].marks=mt[iu].marks+i;
																																									}
																																							}
																																					}
																																			}
																																	}
																															}
																													}
																											}
																									}
																							}
																					}
																			}
																	}
															}
													}
											}
										iu++;	
									}
								histo_pie2(m,ia,mt,iy,sub,xa,xb,xc,xd);
							}
					}
			}
		}
	if(ib==2)//JTA
		{
			cout<<"\\t\tWelcome jta"<<endl;
my5:		cout<<"Press '1' for getting a list of marks.\nPress '2' for adding a list of marks.\nPress '3' for requesting to Prof. "<<endl;
			while(cin>>ch)
				{
					if(ch=='q'){goto man;}
					if(ch=='1')//for list of marks.
						{
							cout<<"Enter the year as **** (eg. - '2013') ,then Press Enter.\tEnter the Semester as '1' or '2' , then Press Enter\t Enter the number of exam as '1' or '2' or ....(upto '9'), then Press enter\n ( Press 'q' to go back.) "<<endl;
							cin>>sa;
							if (sa=="q"){goto my5;}
							cin>>sb>>sc;
							sa=sub+sa+sb+sc;
							stoc(sa);
							ifstream in1(a,ios::in);
							ifstream inia(a,ios::in);
							ia=0;
							while(getline(in1,sb))
							{ia++;};
							student mb[ia];
							for( ib=0;ib<ia;ib++)
								{
									inia>>mb[ib].rl>>mb[ib].marks;
								}
							for( ib=0;ib<ia;ib++)//decryting the file.
								{
									mb[ib].rl=decryption(mb[ib].rl);
								};
							ofstream outa("Hello",ios::out); 
							for( ib=0;ib<ia;ib++)//creating other file named Hello
								{
									outa<<mb[ib].rl<<"  "<<mb[ib].marks<<endl;
								}		
							cout<<"List of marks has been sent to file named 'Hello' please rename it before using it again"<<endl;
						}
					if(ch=='2')//adding marks
aka1:					{
							cout<<"Enter the details of the exam \n Enter year as **** (eg. 2013). Press Enter.\n semester as '1' or '2' .Press Enter. \n Enter the No. of Exam as '1','2',....\t Press 'q' for exit" <<endl;//asking for file name ,11 letters is essential because it has to be used in ifstream, which required some manipuation//see stoc function and 'a[]' array. 
							cin>>sy;
							if(sy=="q"){goto my;}
							if(sy.length()!=11){goto aka1;}
							stoc(sy);
							ifstream in1(a,ios::in);
							ifstream inia(a,ios::in);
							ia=0;
							while(getline(in1,sb))
							{ia++;};
							student ma[ia];
							for(ib=0;ib<ia;ib++)
								{
									inia>>ma[ib].rl>>ma[ib].marks;
								};
							for( ib=0;ib<ia;ib++)
								{
									ma[ib].rl=encryption(ma[ib].rl);
								};
							cout<<"Enter the details of the exam \n Enter year as **** (eg. 2013). Press Enter.\n semester as '1' or '2' .Press Enter. \n Enter the No. of Exam as '1','2',...." <<endl;//getting details of exam.
							cin>>sa;
							if (sa=="q"){goto my;}
							cin>>sb>>sc;
							sa=sub+sa+sb+sc;
							stoc(sa);
							ofstream outa2(a,ios::out);
							for( ib=0;ib<ia;ib++)
								{
									outa2<<ma[ib].rl<<"  "<<ma[ib].marks<<endl;
								}
							goto my;}
					if(ch=='3')//for requesting the professor.
						{
							getline(cin,sk);
my6:						cout<<"enter your request"<<endl;
							getline(cin,sk);
							if(sk=="q"){goto my5;}
							sa=sub+"update";
							stoc(sa);
							ofstream   ouy(a,ios::app);
							ouy<<encryption(sk)<<"-  request by:"<<encryption(user)<<endl;
							goto my6;}
							goto my5;}
						}
	if(ib==3)//ADMIN
		{
			cout<<"\n\n\t\t\tWelcome  ADMIN"<<endl;
			cout<<"Here you can create new users for accessing the datas of students"<<endl;//creating new users.
mypas:		cout<<"Enter the subject of User"<<endl;
			cin>>sd;
			if(sd=="q"){goto man;}
			cout<<"Enter the post of user \n '1' for Prof \t '2' for JTA"<<endl;
			cin>>saa;
			sd=sd+"p0000"+saa;//name of file of password and user id of that usbject.
			stoc(sd);
			ofstream outps(a,ios::app);
			ifstream inps(a,ios::in);
			ifstream inps1(a,ios::in);
			ifstream inps2(a,ios::in);
			cout<<"enter the username and password"<<endl;
			cin>>sd>>se;
			while(inps>>sf)
				{
					if(sf==encryption(sd))//if name already present there.change the password.
						{
							inp=1;break;
						}
					else
						{		
							inps>>sf;
						};
				}
			if(inp==0)//append the file.
				{
					outps<<encryption(sd)<<"  "<<encryption(se)<<endl;
				}
			else //if user name present , change the password.
				{
					while(getline(inps1,sf)){inp++;};
					inp=inp-1;
					pass1 asd[inp];
					for(int ind1=0;ind1<inp;ind1++ )
						{
							inps2>>asd[ind1].use>>asd[ind1].pas;
						}
					for(int ind1=0;ind1<inp;ind1++ )
						{
							if(encryption(sd)==asd[ind1].use)
								{
									asd[ind1].pas=encryption(se);
								}
						}
					ofstream outps1(a,ios::out);
					for(int ind1=0;ind1<inp;ind1++ )
						{
							outps1<<asd[ind1].use<<"  "<<asd[ind1].pas<<endl;
						}
					}
					goto mypas;
				
		} 
	if(ib==4)//Wrong user id
		{
			cout<<"wrong user id "<<endl; goto man;
		}
	if(ib==5)//Wrong password.
		{
				cout<<" wrong password  "<<endl;goto man;
		}
man: return 0;
}










	
