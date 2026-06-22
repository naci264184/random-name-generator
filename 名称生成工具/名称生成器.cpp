#include<iostream>
using namespace std;
#include<fstream>
#include<string>
#include <ctime>
#include <Windows.h>

//测试注释，内容1

void cl_wb1();						//处理文本1（获取汉字库）
void cl_wb2();						//处理文本2（删除由于转成ANSI格式后，错误显示的汉字）
void cl_wb3();						//处理文本3（提取前面3500字）
void cl_wb4();						//处理文本4（去掉不合适汉字）
void cl_wb();						//处理文本
int sc_sjs(int zsl);				//生成_随机数，参数：总数量（如：10，则为0~9的随机数值）
void sc_sjmc();						//生成_随机名称
void jm();							//界面
void cl_yhsr();						//处理用户输入

bool sf_ckscgc = 1;					//是否在终端中查看生成过程
int sj_fw = 2999;					//随机的汉字数范围，这里建议2499或3499（汉字库中3500后面的字不常用，还有随机算法不优秀，取3500这样的整数会不够随机）
string y_wb = "通用规范汉字表.txt";		//原文本（原始文本“通用规范汉字表”，带有编号和拼音）
string clh_wb1 = "去掉拼音和编号.txt";	//处理后文本1（去掉拼音和编号）
string clh_wb2 = "去掉错误汉字.txt";	//处理后文本2（去掉错误汉字），这一步目前没有实际作用，因为错误汉字在3500字后面，3500后的字不会用到
string clh_wb3 = "提取前面3500字.txt";	//处理后文本3（提取前面3500字）
string clh_wb4 = "去掉不合适汉字.txt";	//处理后文本4（去掉不合适汉字）
string bhs_hz = "不合适汉字.txt";		//记录不合适汉字的文本
string hzk1 = "汉字库.txt";				//汉字库的名称1
string hzk2 = "hzk.txt";				//汉字库的名称2

int main()
{
	srand((unsigned int)time(NULL));

	jm();
	system("cls");

	//cl_wb();

	while (1)
	{
		cl_yhsr();					//判断用户的输入并处理
		sc_sjmc();					//如果用户输入1，则退出那个函数，调用这一条函数生成随机名称

		system("pause");
		system("cls");
	}
	

	system("pause");
	return 0;
}


void cl_wb1()
{
	ifstream ifs;
	ofstream ofs;

	ifs.open(y_wb, ios::in);				//打开原文本
	ofs.open(clh_wb1, ios::out);			//打开处理后文本1

	if (!ifs.is_open())
	{
		cout << "文件打开失败" << endl;
		ifs.close();
		return;
	}

	string str;
	int hs = 0;

	while (getline(ifs, str))
	{
		hs++;
	}
	cout << "行数为：" << hs << endl;
	ifs.close();
	ifs.open(y_wb, ios::in);

	for (int i = 0;i < hs;i++)
	{
		getline(ifs, str);
		//cout << str[5] << str[6] << endl;
		ofs << str[5] << str[6] << endl;
	}

	cout << "已去掉编号和拼音" << endl;

	ifs.close();
	ofs.close();
}
void cl_wb2()
{
	ifstream ifs;
	ofstream ofs;

	ifs.open(clh_wb1, ios::in);
	ofs.open(clh_wb2, ios::out);

	if (!ifs.is_open())
	{
		cout << "文件打开失败" << endl;
		ifs.close();
		return;
	}

	string str;
	int js = 0;
	int hz_s = 0;

	while (getline(ifs, str))
	{
		hz_s++;
	}
	cout << "汉字数为：" << hz_s << endl;
	ifs.close();
	ifs.open(clh_wb1, ios::in);

	for (int i = 0;i < hz_s;i++)
	{
		getline(ifs, str);
		if (str == "??" || str == "?\t")
		{
			cout << i + 1 << "： 错误汉字" << endl;
			js++;
			continue;
		}
	
		ofs << str << endl;
	}

	cout << "删除了" << js << "个错误汉字" << endl;
	cout << "剩余" << hz_s - js << "个汉字" << endl;

	ifs.close();
	ofs.close();
}
void cl_wb3()
{
	ifstream ifs;
	ofstream ofs;

	ifs.open(clh_wb1, ios::in);
	ofs.open(clh_wb3, ios::out);

	if (!ifs.is_open())
	{
		cout << "文件打开失败" << endl;
		ifs.close();
		return;
	}

	string str;
	int hz_s = 0;

	while (getline(ifs, str))
	{
		hz_s++;
	}
	cout << "汉字数为：" << hz_s << endl;
	ifs.close();
	ifs.open(clh_wb1, ios::in);

	for (int i = 0;i < hz_s && i < 3500;i++)
	{
		getline(ifs, str);
		ofs << str << endl;
	}

	cout << "已提取前面3500字" << endl;

	ifs.close();
	ofs.close();
}
void cl_wb4()
{
	ifstream ifs;
	ofstream ofs;
	ifstream ifs2;

	int hzk_mc = 1;					//汉字库使用的文本名

	//1.判断文件是否能打开
	ifs.open(clh_wb3, ios::in);
	ofs.open(clh_wb4, ios::out);
	ifs2.open(bhs_hz, ios::in);

	if (!ifs.is_open())				//如果没有"提取前面3500字.txt"文本
	{
		//cout << "文件打开失败" << endl;
		ifs.close();

		ifs.open(hzk1, ios::in);		//则尝试打开"汉字库.txt"文本
		if (!ifs.is_open())				//如果还是没有
		{
			//cout << "文件打开失败" << endl;
			ifs.close();

			ifs.open(hzk2, ios::in);	//则尝试打开"hzk.txt"文本
			if (!ifs.is_open())
			{
				cout << "缺少文件\"" << hzk1 << "\"或\"" << hzk2 << "\"或\"" << clh_wb3 << "\"" << endl;
				ifs.close();
				return;					//还是没有就直接退出
			}
			else
			{
				hzk_mc = 3;
			}
		}
		else
		{
			hzk_mc = 2;
		}
	}

	if (!ifs2.is_open())
	{
		cout << "缺少文件\"" << bhs_hz << "\"" << endl;
		ifs2.close();
		return;
	}
	ifs2.close();

	//2.创建变量
	string str;
	string str2;
	int js = 0;					//计数
	int js2 = 1;				//计数2
	int hz_s = 0;				//汉字库中的汉字数量
	int dq_wz = 0;				//string字符串中的当前下标位置
	int zfc_cd = 0;				//string字符串的长度
	bool sf_zdbhsz = false;		//是否找到不合适字

	//3.获取汉字库中的汉字数量
	while (getline(ifs, str))
	{
		hz_s++;
	}
	cout << "汉字数为：" << hz_s << endl;
	ifs.close();

	if (hzk_mc == 1)
	{
		ifs.open(clh_wb3, ios::in);
	}
	else if (hzk_mc == 2)
	{
		ifs.open(hzk1, ios::in);
	}
	else if (hzk_mc == 3)
	{
		ifs.open(hzk2, ios::in);
	}


	//4.去掉文本中的对应不合适汉字
	for (int i2 = 0;i2 < hz_s;i2++)
	{
		getline(ifs, str);
		sf_zdbhsz = false;
		js2 = 1;

		ifs2.open(bhs_hz, ios::in);
		while (getline(ifs2, str2))			//读取一次文件内容
		{
			zfc_cd = str2.size();			//重新获取字符串长度
			dq_wz = 0;						//重新更新下标位置
			//cout << "第" << js2 << "段：" << endl;
			//cout << "字符串大小：" << zfc_cd << endl;			

			while (dq_wz < zfc_cd && dq_wz + 1 < zfc_cd)
			{
				if (str[0] == str2[dq_wz] && str[1] == str2[dq_wz + 1])
				{
					cout << i2 << "： " << str << endl;
					js++;
					sf_zdbhsz = true;
					break;
				}
				dq_wz += 2;
			}
			if (sf_zdbhsz == true)
			{
				break;
			}

			js2++;
			//cout << endl;
		}
		ifs2.close();

		if (sf_zdbhsz == true)
		{

		}
		else
		{
			ofs << str << endl;
		}
	}

	cout << "删除了" << js << "个不合适汉字" << endl;
	cout << "剩余" << hz_s - js << "个汉字" << endl;

	ifs.close();
	ofs.close();
}
void cl_wb()
{	
	//1.第一步
	//cl_wb1();				//去掉编号和拼音
	//system("pause");

	//2.第二步
	//cl_wb2();				//删除错误汉字
	//system("pause");

	//3.第三步
	cl_wb3();				//提取前面3500字
	system("pause");

	//4.第四步
	cl_wb4();				//去掉不合适汉字
	system("pause");

	system("cls");
}
int sc_sjs(int zsl)						//参数：总数量，返回值：随机结果（数值从0开始，如果需要数值从某值开始，可以在返回结果上加上该数值）
{
	int s = 0;							//数

	int ws1 = 0;						//第一位数
	int ws2 = 0;						//第一位数的范围
	int ws3 = 0;
	int ws4 = 0;
	int ws_fw1 = 0;						//第一位数的范围
	int ws_fw2 = 0;
	int ws_fw3 = 0;
	int ws_fw4 = 0;

	//srand((unsigned int)time(NULL));	//这条随机数种子不能放在函数内，必须设置在main函数中
	if (zsl < 10)						//如果总数量为一位数
	{
		if (zsl <= 0)					//如果传入的总数量小于或等于0
		{
			return 0;					//返回0
		}
		return rand() % zsl;
	}
	else if (zsl < 100)					//如果总数量不小于10，且小于100（两位数）
	{
		ws_fw1 = zsl / 10;				//获取十位数的最大数（范围）
		ws1 = rand() % ws_fw1 + 1;
		if (ws1 == ws_fw1)				//如果十位数的数值，等于最大范围数
		{
			ws_fw2 = zsl % 10;
			ws2 = rand() % (ws_fw2 + 1);
		}
		else
		{
			ws2 = rand() % 10;
		}
		s = ws1 * 10 + ws2;
	}
	else if (zsl < 1000)
	{
		ws_fw1 = zsl / 100;				//获取百位数的最大数（范围）
		ws1 = rand() % ws_fw1 + 1;

		if (ws1 == ws_fw1)				//如果百位数的数值，等于最大范围数
		{
			ws_fw2 = zsl / 10 % 10;
			ws2 = rand() % (ws_fw2 + 1);
		}
		else
		{
			ws2 = rand() % 10;
		}

		if (ws1 == ws_fw1 && ws2 == ws_fw2)		//如果百位数的数值，等于最大范围数，且十位数的数值，等于最大范围
		{
			ws_fw3 = zsl % 10;
			ws3 = rand() % (ws_fw3 + 1);
		}
		else
		{
			ws3 = rand() % 10;
		}
		s = ((ws1 * 10) + ws2) * 10 + ws3;
	}
	else if (zsl < 10000)
	{
		ws_fw1 = zsl / 1000;				//获取千位数的最大数（范围）
		ws1 = rand() % ws_fw1 + 1;

		if (ws1 == ws_fw1)					//如果千位数的数值，等于最大范围数
		{
			ws_fw2 = zsl / 100 % 10;
			ws2 = rand() % (ws_fw2 + 1);
		}
		else
		{
			ws2 = rand() % 10;
		}

		if (ws1 == ws_fw1 && ws2 == ws_fw2)			//如果千位数的数值，等于最大范围数，且百位数的数值，等于最大范围
		{
			ws_fw3 = zsl / 10 % 10;
			ws3 = rand() % (ws_fw3 + 1);
		}
		else
		{
			ws3 = rand() % 10;
		}

		if (ws1 == ws_fw1 && ws2 == ws_fw2 && ws3 == ws_fw3)//如果千位数的数值，等于最大范围数，且百位数的数值，等于最大范围，且十位数的数值，等于最大范围
		{
			ws_fw4 = zsl % 10;
			ws4 = rand() % (ws_fw4 + 1);
		}
		else
		{
			ws4 = rand() % 10;
		}

		s = (((ws1 * 10) + ws2) * 10 + ws3) * 10 + ws4;
	}

	if (s == zsl)			//如果最后随机的结果为数的最大值，必须-1（因为，如果最大值为10，则应该只有0~9的范围，不能是10）
	{
		s - 1;
	}

	return s;
}
void sc_sjmc()
{
	int hz_s = 0;					//汉字数（汉字库里的汉字数）
	int hzk_mc = 1;					//汉字库使用的文本名

	ifstream ifs;
	ofstream ofs;

	//汉字库的第一种文本名称"hzk.txt"
	ifs.open(hzk1, ios::in);
	if (!ifs.is_open())
	{
		//cout << "文件打开失败" << endl;
		hzk_mc = 2;
		ifs.close();
		//return;

		//2.汉字库的第二种文本名称"汉字库.txt"
		ifs.open(hzk2, ios::in);
		if (!ifs.is_open())
		{
			cout << "缺少文件\"" << hzk1 << "\"或\"" << hzk2 << "\"" << endl;
			ifs.close();
			return;
		}
	}
	
	ifs.close();

	ofs.open("名称.txt", ios::out);

	string str;
	/*/
	while (getline(ifs, str))
	{
		hz_s++;		
	}
	cout << "汉字数为：" << hz_s << endl << endl;
	ifs.close();
	//*/
	

	int mc_zs = 0;			//名称_字数
	int hz_bh = 0;			//汉字_编号（选汉字库的哪个汉字）

	for (int i = 0;i < 100;i++)
	{
		mc_zs = sc_sjs(3) + 2;
		if (sf_ckscgc)
		{
			cout << "名称_字数：" << mc_zs << endl;
		}

		for (int i2 = 0;i2 < mc_zs;i2++)
		{
			//hz_bh = sc_sjs(hz_s);
			hz_bh = sc_sjs(sj_fw) + 1;			//只有前面3500个汉字是常用的，但是由于随机数算法的问题，这里设置为2999概率才平均

			if (sf_ckscgc)
			{
				cout << "汉字_编号：" << hz_bh << endl;
			}
		
			if (hzk_mc == 1)
			{			
			ifs.open(hzk1, ios::in);
			}
			else if (hzk_mc == 2)
			{
				ifs.open(hzk2, ios::in);
			}

			for (int i3 = 1;i3 < sj_fw + 1;i3++)
			{
				getline(ifs, str);
				if (i3 == hz_bh)
				{
					if (sf_ckscgc)
					{
						cout << "字：" << str << endl;
					}
					
					ofs << str;
					break;
				}
			}
			ifs.close();
		}

		if (sf_ckscgc)
		{
			cout << endl;
		}
		
		if (i % 5 == 4)
		{
			ofs << endl;
		}
		else
		{
			if (mc_zs <= 2)
			{
				ofs << "\t\t\t";
			}
			else
			{
				ofs << "\t\t";
			}
		}
	}
	//ofs << endl;

	ifs.close();
	ofs.close();
}
void jm()
{
	cout << "名称生成器" << endl;
	cout << endl;
	cout << "1.生成一次" << endl;
	cout << "2.打开/关闭 显示生成过程（默认打开）" << endl;
	cout << "3.更新汉字库" << endl;
	cout << "4.退出" << endl;
	cout << "0.返回" << endl;

	for (int i = 0;i < 22;i++)
	{
		cout << endl;
	}
	system("pause");
}
void cl_yhsr()
{
	string sr = "";

	while (1)
	{
		cout << "当前汉字随机范围：" << sj_fw << "\t\t\t（返回键为0）" << endl;
		cout << "请输入您要进行的操作" << endl;

		cin >> sr;
		if (sr == "1")
		{
			return;
		}
		else if (sr == "2")
		{
			if (sf_ckscgc == true)
			{
				sf_ckscgc = false;
				cout << "已关闭名称生成过程" << endl;
			}
			else if (sf_ckscgc == false)
			{
				sf_ckscgc = true;
				cout << "已打开名称生成过程" << endl;
			}
		}
		//*/
		else if (sr == "3")
		{
			cl_wb4();				//去掉不合适汉字
		}
		//*/
		else if (sr == "4")
		{
			cout << "已成功退出" << endl;
			system("pause");
			exit(0);
		}
		else if (sr == "0")
		{
			system("cls");
			jm();
			system("cls");
			continue;
		}
		else
		{
			cout << "请输入有效内容" << endl;
		}

		system("pause");
		system("cls");
	}
}