#ifndef MANAGER_H
#define MANAGER_H

#include <string>
#include <vector>

//读取输入的函数
std::string readDate(const std::string& prompt);  
std::string readString(const std::string& prompt);
int readInt(const std::string& prompt);
double readDouble(const std::string& prompt);

//销售信息
struct SaleRecord { 
	std::string category;       //种类
	std::string name;           //名称
	std::string brand;          //品牌
	int quantity;               //数量
	double totalProfit;         //总利润
	std::string saleDate;       //销售日期
	// 重载小于运算符，用于按日期排序
	bool operator < (const SaleRecord& other) const {
		return saleDate < other.saleDate;
	}
	// 构造函数
	SaleRecord(const std::string& cat, const std::string& n, const std::string& b, int q, double profit, const std::string& date);
};

//进货信息
struct PurchaseRecord { 
	std::string category;       //种类
	std::string name;           //名称
	std::string brand;          //品牌
	std::string manufacturer;   //进货厂家
	float purchasePrice;        //进价
	int quantity;               //数量
	std::string addDate;        //进货日期
	// 重载小于运算符，用于按日期排序
	bool operator < (const PurchaseRecord& other) const {
		return addDate < other.addDate;
	}
	// 构造函数
	PurchaseRecord(const std::string& cat, const std::string& n, const std::string& b, const std::string& manu, float price, int q, const std::string& date);
};

//商品库存
struct Product { 
	std::string category;       //种类
	std::string name;           //名称
	std::string brand;          //品牌
	int stock;                  //库存
	float price;                //售价
	float purchasePrice;        //进价
	
	// 重载小于运算符，用于排序，按库存数量从大到小排序
	bool operator < (const Product& other) const {
		return stock > other.stock; 
	}
	
	// 构造函数
	Product(const std::string& cat, const std::string& n, const std::string& b, int s, float p, float purchaseP);
};

class Manager {
public:
	
	void addProduct();   		//1.进货         	创建进货信息，并且添加库存	(种类名称品牌相同的可以合并，品牌不同的算作不同商品但是同名)
	void sellProduct();  		//2.出货			创建出货信息，并且减少库存 	(出售时要说明品牌)
	void editProduct();    		//3.修改商品    	1.先找到某种商品(种类名称品牌) 然后修改(种类名称品牌库存进价售价等信息)
	void deleteProduct();       //4.删除商品   		通过种类名称品牌 直接从库存中删除某种商品的记录
	void searchProduct(); 		//5.查询功能  		输入某商品(种类名称品牌) 1.输出商品的库存信息 2.输出某商品的进货记录 3.输出某商品的销售记录
	void displayStatistics();	//6.统计功能   		1.统计所有库存,输出一个表格（按照库存量由大到小排列) 2.输出所有进货记录(按照日期排列)  3.输出所有销售记录(按照日期排列)
	void displayprofit();       //7.计算利润   		1.输出一周内每种商品的利润（为0的不输出）  2.一周内四类商品的利润  (都要按照利润额从大到小排列)
	void saveToFile();			//8.退出并保存文件   
	void loadFromFile();		//进入自动读取文件	
	
	//实现查询并排序输出
	void searchInventory(const std::string& category, const std::string& name, const std::string& brand);
	void searchPurchases(const std::string& category, const std::string& name, const std::string& brand);
	void searchSales(const std::string& category, const std::string& name, const std::string& brand);
	
	
private:
	std::vector<Product> products; 		// 当前商品
	std::vector<SaleRecord> sales;	 	// 存放销售记录
	std::vector<PurchaseRecord> purchases; 	// 存放进货记录
};

#endif


