#include <Windows.h>
#include<iostream>
using namespace std;
#include<fstream>
#include<string>
#include <ctime>
#include <random>
#include <filesystem>

//基础_方法
#if 0
void cl_wb1();						//处理文本1（获取汉字库）
void cl_wb2();						//处理文本2（删除由于转成ANSI格式后，错误显示的汉字）
void cl_wb3();						//处理文本3（提取前面3500字）
#endif
void jm();								//界面
int cl_yhsr();							//处理用户输入
int GetRandomNumber(int min, int max);	//参数：最小值, 最大值
bool jc_wjsfcz();						//检测文件是否存在
void qc_wjnr();							//清除"输出结果文件"原内容

//生成过程_方法
void sc();							//生成（包括排除汉字、生成名称、排除汉字组合）
void pc_hz();						//排除汉字（去掉不合适汉字）
int jc_hzsz(string& path);			//检测_汉字数量
void sc_sjmc();						//生成_随机名称
bool pc_hzzh();						//排除汉字组合
void xr_wj(int& i);					//将生成结果，写入文件中

//路径_变量
#if 0
string y_wb = "assets\\raw\\通用规范汉字表.txt";		//原文本（原始文本“通用规范汉字表”，带有编号和拼音）
string clh_wb1 = "去掉拼音和编号.txt";					//处理后文本1（去掉拼音和编号）
string clh_wb2 = "去掉错误汉字.txt";					//处理后文本2（去掉错误汉字），这一步目前没有实际作用，因为错误汉字在3500字后面，不会用到
string clh_wb3 = "assets\\raw\\3500字(未过滤前).txt";	//处理后文本3（提取前面3500字）
#endif
string chinese_characters = "assets\\chinese_characters.txt";	//程序实际使用的汉字库
string unwanted_chars = "assets\\unwanted_chars.txt";			//不合适单字黑名单
string filtered_chars = "temp\\data\\filtered_chars.txt";		//过滤后的汉字
string unwanted_words = "assets\\unwanted_words.txt";			//不合适词组黑名单
string generated_names = "temp\\data\\generated_names.txt";		//生成结果

//数据、状态_变量
bool sf_ckscgc = 1;					//是否在终端中查看生成过程
bool sf_scpcgc = 0;					//是否输出汉字排除过程
bool sf_scczpc = 1;					//是否输出词组排除过程
bool sf_cscspc = 0;					//是否_测试词组排除过程（将名称_生成结果的值，故意修改为一个非常词组）
int sj_fw = 3500;					//随机的汉字数范围，这里建议2499或3499（汉字库中3500后面的字不常用，还有随机算法不优秀，取3500这样的整数会不够随机）
string mc_scjg = "";				//名称_生成结果
int mc_zs = 0;						//名称_字数
namespace fs = std::filesystem;		//将fs设置为命名空间filesystem
string lssj_ml = "temp/data";		//临时数据目录
int yh_xz = 0;						//用户选择

int main()
{	
	//在当前目录下，创建一个临时数据目录，如果目录存在会自动跳过
	fs::create_directories(lssj_ml);

	jm();

	while (1)
	{
		system("cls");

		//1.检测文件是否存在
		if (!jc_wjsfcz())
		{
			system("pause");
			system("cls");
			continue;
		}

		//2.处理用户输入
		yh_xz = cl_yhsr();					//判断用户的输入并处理
		if (yh_xz != 1)
		{
			continue;
		}

		//3.生成100次结果（包括：生成_随机名称、排除汉字组合并重新生成）
		sc();

		//4.提示用户已生成完成，并打开文件查看生成结果
		cout << endl;
		cout << "生成完成" << endl;
		system(generated_names.c_str());

		//system("pause");
		system("cls");
	}
	

	system("pause");
	return 0;
}

#if 0
void cl_wb1()
{
	ifstream ifs;
	ofstream ofs;

	ifs.open(y_wb, ios::in);				//打开原文本
	ofs.open(clh_wb1, ios::out);			//打开处理后文本1

	if (!ifs.is_open())
	{
		cout << "文件打开失败：" << y_wb << endl;
		//system("pause");
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
		cout << "文件打开失败：" << clh_wb1 << endl;
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
		cout << "文件打开失败：" << clh_wb1 << endl;
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
#endif
void jm()
{
	cout << "名称生成器" << endl;
	cout << endl;
	cout << "1.生成一次" << endl;
	cout << "2.打开/关闭 显示生成过程（默认打开）" << endl;
	//cout << "3.更新汉字库" << endl;
	cout << "3.退出" << endl;
	cout << "0.返回" << endl;

	for (int i = 0;i < 23;i++)
	{
		cout << endl;
	}
	system("pause");
}
int cl_yhsr()


{
	string sr = "";

	while (1)
	{
		cout << "当前汉字随机范围：" << sj_fw << "\t\t\t（返回键为0）" << endl;
		cout << "请输入您要进行的操作" << endl;

		cin >> sr;
		if (sr == "1")
		{
			return 1;
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

			system("pause");
			return 2;
		}
		/*/
		else if (sr == "3")
		{
			cl_wb();				//去掉不合适汉字
		}
		//*/
		else if (sr == "3")
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
int GetRandomNumber(int min, int max)		//参数：最小值, 最大值
{
	/*/
	// 1. 静态设备：只构造一次，用于获取系统真随机种子
	static std::random_device rd;
	// 2. 静态引擎：只初始化一次，之后状态持续向前推进
	static std::mt19937 gen(rd());
	// 3. 静态分布：只定义一次，范围 1~10000
	static std::uniform_int_distribution<int> dist(1, 10000);
	//*/

	// 1. 引擎（含种子）：整个程序只播种一次，并且不长期占用 random_device 资源
	static std::mt19937 gen(std::random_device{}());

	// 2. 分布规则：不用 static，每次根据传入的参数动态创建（极轻量，无性能负担）
	std::uniform_int_distribution<int> dist(min, max);

	// 每次调用只执行这一句，返回不同的数
	return dist(gen);
}
bool pdlj(string path)							//判断路径（是否可以打开）
{
	ifstream ifs;
	ifs.open(path, ios::in | ios::binary);
	if (ifs.is_open())							//如果打开成功
	{
		ifs.close();
		return true;							//返回true
	}
	else										//否则（打开失败）
	{
		ifs.close();
		return false;							//返回false
	}
}
bool jc_wjsfcz()
{
	ifstream ifs;
	bool sf_czwj = true;		//是否_存在文件

	//1.汉字库
	ifs.open(chinese_characters, ios::in);
	if (!ifs.is_open())
	{
		cout << "缺少文件：" << chinese_characters << endl;		
		sf_czwj = false;
	}

	//2.不合适汉字
	ifs.close();
	ifs.open(unwanted_chars, ios::in);
	if (!ifs.is_open())
	{
		cout << "缺少文件：" << unwanted_chars << endl;
		sf_czwj = false;
	}

	//3.不合适词组
	ifs.close();
	ifs.open(unwanted_words, ios::in);
	if (!ifs.is_open())
	{
		cout << "缺少文件：" << unwanted_words << endl;
		sf_czwj = false;
	}

	//如果不存在文件，则返回false
	if (sf_czwj == false)
	{
		return false;
	}

	ifs.close();
	return true;					//存在文件，返回true
}
void qc_wjnr()
{
	//1.打开文件
	ofstream ofs;
	ofs.open(generated_names, ios::out);

	ofs.close();
}

void sc()
{
	//1.获取排除范围，并排除不合适汉字
	jc_hzsz(chinese_characters);
	pc_hz();
	cout << "汉字排除完成" << endl << endl;

	//2.获取生成范围（获取汉字数），并清除"输出结果文件"原内容
	jc_hzsz(filtered_chars);
	qc_wjnr();
	cout << "已重新获取汉字范围" << endl << endl;

	//3.循环生成100个随机名称，并排除掉不合适词组
	for (int i = 0;i < 100;i++)
	{
		//3.1 生成一次随机名称
		sc_sjmc();


		//3.2 检测是否存在不合适词组
		if (pc_hzzh())				//如果存在，则取消该次生成结果，退回循环重新生成一次
		{
			i--;
			// * 测试内容_查看词组排除过程（允许删除），共5处
			if (sf_cscspc)
			{
				cout << "i为：" << i << endl;
			}			
			continue;
		}

		//3.3 将生成结果写入文件
		xr_wj(i);
	}
}
void pc_hz()					//排除_不合适汉字
{
	ifstream ifs;
	ofstream ofs;
	ifstream ifs2;

	//1.创建变量
	string str;
	string str2;
	int js = 0;					//计数（记录删除的汉字数量）
	int dq_wz = 0;				//string字符串中的当前下标位置
	int zfc_cd = 0;				//string字符串的长度
	bool sf_zdbhsz = false;		//是否找到不合适字

	//2.读取文本
	ifs.open(chinese_characters, ios::in);		//读取汉字库.txt
	ofs.open(filtered_chars, ios::out);			//写入过滤后汉字.txt

	//3.将"汉字库.txt"的汉字，经过"不合适汉字.txt"的筛选后，将过滤后的结果放入"过滤后汉字.txt"中
	for (int i2 = 0;i2 < sj_fw;i2++)
	{
		//3.1 读取汉字库的一行
		getline(ifs, str);
		sf_zdbhsz = false;

		//3.2 读取"不合适汉字.txt"的一行（共两行）
		ifs2.open(unwanted_chars, ios::in);
		while (getline(ifs2, str2))	//共循环两次
		{
			zfc_cd = str2.size();			//重新获取字符串长度
			dq_wz = 0;						//重新更新下标位置

			//3.3 遍历"不合适汉字.txt"的这一行内容的所有字，是否有跟汉字库这一次汉字相同的
			while (dq_wz < zfc_cd && dq_wz + 1 < zfc_cd)
			{
				if (str[0] == str2[dq_wz] && str[1] == str2[dq_wz + 1])
				{
					//是否_显示排除过程
					if (sf_scpcgc)
					{
						//cout << i2 << "： " << str << endl;
						cout << "汉字_编号：" << i2 << "\t\t字：" << str << endl;
					}

					js++;
					sf_zdbhsz = true;
					break;
				}
				dq_wz += 2;
			}

			//3.4 如果找到"不合适汉字.txt"的某一行，的某一个字，跟汉字库这一次汉字相同，则直接退出，进入下一次的汉字库汉字排查
			if (sf_zdbhsz == true)
			{
				break;
			}
		}
		ifs2.close();

		//4.经过排除后，如果这次"汉字库.txt"的汉字，在"不合适汉字.txt"的排除范围内未找到，则将这个汉字放入"过滤后汉字.txt"中
		if (sf_zdbhsz == false)
		{
			ofs << str << endl;
		}
	}

	//5.输出排除结果
	if (sf_scpcgc)
	{
		cout << "删除了" << js << "个不合适汉字" << endl;
		cout << "剩余" << sj_fw - js << "个汉字" << endl;
	}

	ifs.close();
	ofs.close();
}
int jc_hzsz(string& path)
{
	//1.创建变量
	ifstream ifs;
	string str;
	int hz_s = 0;

	//2.打开文件
	ifs.open(path, ios::in);

	//3,循环读取内容，检测汉字数量
	while (getline(ifs, str))
	{
		hz_s++;
	}
	cout << "汉字数为：" << hz_s << endl;
	ifs.close();

	sj_fw = hz_s;
}
void sc_sjmc()
{
	//1.创建变量
	ifstream ifs;
	string str;
	int hz_bh = 0;			//汉字_编号（选汉字库的哪个汉字）
	mc_scjg = "";			//刷新记录内容

	//2.生成名称长度
	mc_zs = GetRandomNumber(2, 4);
	if (sf_ckscgc)
	{
		cout << "名称_字数：" << mc_zs << endl;
	}

	//3.生成多次汉字，并将它们组成一个词（名称）
	for (int i2 = 0;i2 < mc_zs;i2++)
	{
		//3.1 生成一个随机汉字编号
		hz_bh = GetRandomNumber(1, sj_fw);
		if (sf_ckscgc)
		{
			cout << "汉字_编号：" << hz_bh << endl;
		}

		//3.2 打开文件
		ifs.open(filtered_chars, ios::in);

		//3.3 循环读取"汉字库.txt"，直到"当前读取的次数"为"汉字对应编号"，则将"该汉字"加入"mc_scjg字符串"中
		for (int i3 = 1;i3 < sj_fw + 1;i3++)
		{
			getline(ifs, str);
			if (i3 == hz_bh)
			{
				if (sf_ckscgc)
				{
					cout << "字：" << str << endl;
				}

				mc_scjg += str;
				break;
			}
		}
		ifs.close();
	}

	if (sf_ckscgc)
	{
		cout << endl;
	}
}
bool pc_hzzh()			//排除不合适汉字组合
{
	//1.创建变量
	ifstream ifs;	
	string str = "";

	//2.打开文件
	ifs.open(unwanted_words, ios::in);

	// * 测试内容_查看词组排除过程（允许删除），共5处
	if (sf_cscspc)
	{
		mc_scjg = "添加1";
		cout << "已将\"名称生成结果\"的值修改为：\"" << mc_scjg << "\"" << endl;
		cout << "非法词组排除过程：" << endl;
	}

	//3.循环读取不合适词组
	while (ifs >> str)
	{
		//4.如果在"名称结果"中，可以找到该"不合适词组"
		if (mc_scjg.find(str) != string::npos)
		{
			// * 测试内容_查看词组排除过程（允许删除），共5处
			if (sf_scczpc)
			{
				cout <<"出现非法词组："<<str << "\t\t已忽略该次生成结果" << endl;
				
				if (sf_cscspc)
				{
					system("pause");
				}
			}

			ifs.close();
			return true;
		}
		// * 测试内容_查看词组排除过程（允许删除），共5处
		else if(sf_cscspc)
		{
			cout << "\"" << mc_scjg << "\"中，不存在\"" << str << "\"" << endl;
		}
	}
	// * 测试内容_查看词组排除过程（允许删除），共5处
	if (sf_cscspc)
	{
		cout << "未出现非法词组" << endl;
	}	

	ifs.close();
	return false;
}
void xr_wj(int& i)				//将生成结果，写入文件中
{
	//1.打开文件
	ofstream ofs;
	ofs.open(generated_names, ios::out | ios::app);

	//2.将该次生成结果，写入文件中
	ofs << mc_scjg;

	//3.换行或加入间隙
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

	ofs.close();
}