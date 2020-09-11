#include "pigfarm.h"
using namespace std;
PigFarm::PigFarm() 
{
    this->totalPigNums=0;
    this->totalBlackPigNums=0;
    this->totalSmallFlowerPigNums=0;
    this->totalBigWhightPigNums=0;
    this->flowerPigStyIndex=0;
}
void PigFarm::salePigs()
{
    int blackPig=0,smallFlowerPig=0,bigWhightPig=0;
    double totalSalePrice=0;
    Pig*q;
    for(int i=0;i<PigFarm::totalPigStyNums;i++)
    {
        for(Pig*p=this->pigStys[i].first();p!=this->pigStys[i].last()->succ;p=p->succ)
        {
            if(p->getWeight()>Pig::weightMax||(p->getGrowDay()-360)>0)//���س���150��ĺ���������1����������г�Ȧ 
            {
                q=p;
                p=p->pred;
                switch(q->getBreed())
                {
                    case 0:
                    blackPig++;
                    totalSalePrice+=(q->getWeight()*Pig::salesPrice[0]);
                    break;
                    case 1:
                    smallFlowerPig++;
                    totalSalePrice+=(q->getWeight()*Pig::salesPrice[1]);
                    break;
                    case 2:
                    bigWhightPig++;
                    totalSalePrice+=(q->getWeight()*Pig::salesPrice[2]);
                    break;
                }
                q=this->pigStys[i].removePig(q);
                delete q;
            }
        }
    }
    this->decreasePigNums(blackPig,smallFlowerPig,bigWhightPig);
    cout<<"��ι�����"<<blackPig<<"ͷ����      "<<smallFlowerPig<<"ͷС����       "<<bigWhightPig<<"ͷ�����"<<endl;
	cout<<"���γ�Ȧ�����������ۼ�Ϊ: "<<totalSalePrice<<"Ԫ"<<endl;
}
void PigFarm::print()
{
    cout<<"��Ȧ����"<<this->totalPigNums<<"ͷ��"<<"����"<<this->totalBlackPigNums<<"ͷ С����"<<this->totalSmallFlowerPigNums<<"ͷ   ������"<<this->totalBigWhightPigNums<<"ͷ"<<endl;
}
void PigFarm::increasePigNums(int blackPig,int smallFlowerPig,int bigWhightPig)
{
    this->totalPigNums+=(blackPig+smallFlowerPig+bigWhightPig);
    this->totalBlackPigNums+=blackPig;
    this->totalSmallFlowerPigNums+=smallFlowerPig;
    this->totalBigWhightPigNums+=bigWhightPig;
}
void PigFarm::decreasePigNums(int blackPig,int smallFlowerPig,int bigWhightPig)
{
    this->totalPigNums-=(blackPig+smallFlowerPig+bigWhightPig);
    this->totalBlackPigNums-=blackPig;
    this->totalSmallFlowerPigNums-=smallFlowerPig;
    this->totalBigWhightPigNums-=bigWhightPig;
}
void PigFarm::addPigsMenu()
{
	cout<<endl<<"===================================��������======================================="<<endl;
	 cout<<"���ɽ������²�����"<<endl;
		cout<<"\t\t----------------------------------------------------------\n";
		cout<<"\t\t|                                                         |\n";
		cout<<"\t\t|                  1.  �������                           |\n";
		cout<<"\t\t|                                                         |\n";
		cout<<"\t\t|                  2.  �ֶ�����                           |\n";
		cout<<"\t\t|                                                         |\n";
		cout<<"\t\t----------------------------------------------------------\n";
		cout<<endl<<"����������ѡ��"<<endl;
}
void PigFarm::deteAddPigNums(int &blackPig,int &smallFlowerPig,int &bigWhightPig,int &singlePigNum)
{
    int select=0;
    while(true)
    {
    	system("cls");
        this->addPigsMenu();
        cin>>select;
        switch(select)
        {
        	case 1:
        	srand((unsigned)time(NULL));
        	blackPig=rand()%(this->getSurplus()+1);
            smallFlowerPig=rand()%(this->getSurplus()-blackPig+1);
            bigWhightPig=rand()%(this->getSurplus()-blackPig-smallFlowerPig+1);
            cout<<endl<<"�˴��������"<<blackPig<<"ͷ����      "<<smallFlowerPig<<"ͷС����         "<<bigWhightPig<<"ͷ�����"<<endl;
            break;
            case 2:
            	while(true)
	            {
	            	cout<<endl<<"��������Ҫ����ĺ���������: ";
					 cin>>blackPig;
					 cout<<endl<<"��������Ҫ�����С����������: ";
	                cin>>smallFlowerPig;
	                cout<<endl<<"��������Ҫ����Ĵ����������: ";
	                cin>>bigWhightPig;
	                if(blackPig+smallFlowerPig+bigWhightPig>this->getSurplus())
	                {
	                    cout<<endl<<"���������̫�࣬���������޷�װ����Щ��������������";
	                }
	                else
	                {
	                    break;
	                }
	            }
            	break;
            	default:
            		cout<<"������������½���ѡ��"<<endl;
            		system("pause");
            		break;
		}
        bool hasSpace=false;
        for(int i=1;i<=PigSty::pigNumMax;i++)
        {
            if((((this->totalSmallFlowerPigNums+this->totalBigWhightPigNums+smallFlowerPig+bigWhightPig)/i)+((this->totalBlackPigNums+blackPig)/i))>totalPigStyNums)
            {
                continue;
            }
            else
            {
                if((this->totalBlackPigNums+blackPig)%i!=0&&(this->totalSmallFlowerPigNums+this->totalBigWhightPigNums+smallFlowerPig+bigWhightPig)%i!=0)
                {
                    if((((this->totalSmallFlowerPigNums+this->totalBigWhightPigNums+smallFlowerPig+bigWhightPig)/i)+((this->totalBlackPigNums+blackPig)/i))+2>totalPigStyNums)
                    {
                        continue;
                    }
                }
                else if((this->totalBlackPigNums+blackPig)%i!=0||(this->totalSmallFlowerPigNums+this->totalBigWhightPigNums+smallFlowerPig+bigWhightPig)%i!=0)
                {
                    if((((this->totalSmallFlowerPigNums+this->totalBigWhightPigNums+smallFlowerPig+bigWhightPig)/i)+((this->totalBlackPigNums+blackPig)/i))+1>totalPigStyNums)
                    {
                        continue;
                    }
                }
                singlePigNum=i;
                hasSpace=true;
                break;
            }
        }
        if(hasSpace){
        	   cout<<"�������̳ɹ�!"<<endl;
        	   system("pause");
                break;
            }
        else
        {
            cout<<endl<<"������Ȧ���޷�װ����Щ���̣��˴ι���ʧ�ܣ������½���ѡ��"<<endl;
            system("pause");
        }
    }
}
void PigFarm::putPigIntoSty(int c,int d,int singlePigNum,int oneLessNumPigStys,int PigStys,PigBreed::Type breed1,PigBreed::Type breed2)
{
    PigSty temporaryPigSty;
    int t=0,m=oneLessNumPigStys,n=PigStys-oneLessNumPigStys;
    while(m!=0||n!=0)
    {
        if(this->pigStys[t].getPigNum()==0||this->pigStys[t][0].getBreed()==breed1||this->pigStys[t][0].getBreed()==breed2)
        {

            int p=singlePigNum,q=singlePigNum-1;
            if(this->pigStys[t].getPigNum()>p)
            {
                if(n>0)
                {
                    int a=this->pigStys[t].getPigNum()-p;
                    while(a--)
                    {

                        temporaryPigSty.insert(this->pigStys[t].removePig(this->pigStys[t].last()));
                    }
                    n--;
                }
                else
                {
                    int a=this->pigStys[t].getPigNum()-q;
                    while(a--)
                    {
                        temporaryPigSty.insert(this->pigStys[t].removePig(this->pigStys[t].last()));
                    }
                    m--;
                }
            }
            else if(this->pigStys[t].getPigNum()==p)
            {
                if(n>0)n--;
                else
                {
                    temporaryPigSty.insert(this->pigStys[t].removePig(this->pigStys[t].last()));
                    m--;
                }
            }
            else if(this->pigStys[t].getPigNum()==q)
            {
                if(m>0)m--;
                else
                {
                    if(temporaryPigSty.getPigNum()>0)
                    {
                        this->pigStys[t].insert(temporaryPigSty.removePig(temporaryPigSty.last()));
                    }
                    else
                    {
                        if(c>0)
                        {
                            this->pigStys[t].insert(breed1);
                            c--;
                        }
                        else
                        {
                            this->pigStys[t].insert(breed2);
                            d--;
                        }
                    }

                    n--;
                }
            }
            else
            {
                if(m>0)
                {
                    int a=q-this->pigStys[t].getPigNum();
                    while(a--)
                    {
                        if(temporaryPigSty.getPigNum()>0)
                        {
                            this->pigStys[t].insert(temporaryPigSty.removePig(temporaryPigSty.last()));
                        }
                        else
                        {
                            if(c>0)
                            {
                                this->pigStys[t].insert(breed1);
                                c--;
                            }
                            else
                            {
                                this->pigStys[t].insert(breed2);
                                d--;
                            }
                        }

                    }
                    m--;
                }
                else
                {
                    int a=p-this->pigStys[t].getPigNum();
                    while(a--)
                    {
                        if(temporaryPigSty.getPigNum()>0)
                        {
                            this->pigStys[t].insert(temporaryPigSty.removePig(temporaryPigSty.last()));
                        }
                        else
                        {
                            if(c>0)
                            {
                                this->pigStys[t].insert(breed1);
                                c--;
                            }
                            else
                            {
                                this->pigStys[t].insert(breed2);
                                d--;
                            }
                        }
                    }
                    n--;
                }
            }
        }
        t++;
    }
}
void PigFarm::changePigDistribution(int blackPigStys)
{
    if(flowerPigStyIndex<blackPigStys)
    {
        for(int i=flowerPigStyIndex;i<blackPigStys;i++)
        {
            if(this->pigStys[i].getPigNum()==0)continue;
            else
            {
                while(this->pigStys[i].getPigNum()!=0)
                {
                     this->pigStys[blackPigStys].insert(this->pigStys[i].removePig(this->pigStys[i].last()));
                }
            }
        }
     }
    else if(flowerPigStyIndex>blackPigStys)
    {
        for(int i=flowerPigStyIndex-1;i>=blackPigStys;i--)
        {
            if(this->pigStys[i].getPigNum()==0)continue;
            else
            {
                while(this->pigStys[i].getPigNum()!=0)
                {
                     this->pigStys[0].insert(this->pigStys[i].removePig(this->pigStys[i].last()));
                }
            }
        }
    }
    this->flowerPigStyIndex=blackPigStys;
}
void PigFarm::addPigs()
{
    int blackPig=0,smallFlowerPig=0,bigWhightPig=0,singlePigNum=0;
    this->deteAddPigNums(blackPig,smallFlowerPig,bigWhightPig,singlePigNum);

    int extraBlackPigs=(this->totalBlackPigNums+blackPig)%singlePigNum;
    int oneLessNumBlackPigStys=(extraBlackPigs==0)?0:(singlePigNum-extraBlackPigs);
    int blackPigStys=(extraBlackPigs==0)?((this->totalBlackPigNums+blackPig)/singlePigNum):((this->totalBlackPigNums+blackPig)/singlePigNum+1);
    this->changePigDistribution(blackPigStys);

    this->putPigIntoSty(blackPig,0,singlePigNum,oneLessNumBlackPigStys,blackPigStys,PigBreed::black,PigBreed::black);


    int extraFlowerPigs=(this->totalSmallFlowerPigNums+this->totalBigWhightPigNums+smallFlowerPig+bigWhightPig)%singlePigNum;
    int oneLessNumFlowerPigStys=(extraFlowerPigs==0)?0:(singlePigNum-extraFlowerPigs);
    int FlowerPigStys=(extraFlowerPigs==0)?((this->totalSmallFlowerPigNums+this->totalBigWhightPigNums+smallFlowerPig+bigWhightPig)/singlePigNum):((this->totalSmallFlowerPigNums+this->totalBigWhightPigNums+smallFlowerPig+bigWhightPig)/singlePigNum+1);
    this->putPigIntoSty(smallFlowerPig,bigWhightPig,singlePigNum,oneLessNumFlowerPigStys,FlowerPigStys,PigBreed::smallFlower,PigBreed::bigWhight);

    this->increasePigNums(blackPig,smallFlowerPig,bigWhightPig);
}
void PigFarm::pigFarmNextTime(int day)
{
	for(int i=0;i<PigFarm::totalPigStyNums;i++)
	{
		this->pigStys[i].pigStyNextTime(day);
	}
}
void PigFarm::printPigDistribution(PigBreed::Type breed,int lo,int hi)
{
	switch(breed)
	{
		case 0:
			cout<<"������������"<<totalBlackPigNums;
			break;
			case 1:
				cout<<"С������������"<<totalSmallFlowerPigNums; 
				break;
				case 2:
					cout<<"�������������"<<totalBigWhightPigNums;
					break;
	}
	cout<<"ͷ"<<endl;
		cout<<"���У�"<<endl;
	
		int pigNum=0;
	cout<<"������[20-50)kg���У�";
	for(int i=lo;i<hi;i++)
	{
		pigNum+=this->pigStys[i].countPigNumOfWeight(breed,20,49);
	}
	cout<<pigNum<<"ͷ"<<endl;
	pigNum=0;
	cout<<"������[50-75]kg���У�";
	for(int i=lo;i<hi;i++)
	{
		pigNum+=this->pigStys[i].countPigNumOfWeight(breed,50,75);
	}
	cout<<pigNum<<"ͷ"<<endl;
	pigNum=0;
	cout<<"���ش���75kg���У�";
	for(int i=lo;i<hi;i++)
	{
		pigNum+=this->pigStys[i].countPigNumOfWeight(breed,75,1000);
	}
	cout<<pigNum<<"ͷ"<<endl;
	pigNum=0;
	cout<<"����ʱ��С��3���µ��У�";
	for(int i=lo;i<hi;i++)
	{
		pigNum+=this->pigStys[i].countPigNumOfGrowTime(breed,0,3);
	}
	cout<<pigNum<<"ͷ"<<endl;
	pigNum=0;
	cout<<"����ʱ����ڵ���3����С��9���µ��У�";
	for(int i=lo;i<hi;i++)
	{
		pigNum+=this->pigStys[i].countPigNumOfGrowTime(breed,3,9);
	}
	cout<<pigNum<<"ͷ"<<endl;
	pigNum=0;
	cout<<"����ʱ����ڵ���9����С��1����У�";
	for(int i=lo;i<hi;i++)
	{
		pigNum+=this->pigStys[i].countPigNumOfGrowTime(breed,9,12);
	}
	cout<<pigNum<<"ͷ"<<endl;
}

void PigFarm::printEachBreedDistribution()
{
	
	printPigDistribution(PigBreed::black,0,this->flowerPigStyIndex);
	printPigDistribution(PigBreed::smallFlower,this->flowerPigStyIndex,PigFarm::totalPigStyNums);
	printPigDistribution(PigBreed::bigWhight,this->flowerPigStyIndex,PigFarm::totalPigStyNums);
	
}