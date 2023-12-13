#include "Manager.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>
#include <string>
#include <iomanip> 
#include <regex>//正则表达式

SaleRecord::SaleRecord(const std::string& cat, const std::string& n, const std::string& b, int q, double profit, const std::string& date)
: category(cat), name(n), brand(b), quantity(q), totalProfit(profit), saleDate(date) {}

PurchaseRecord::PurchaseRecord(const std::string& cat, const std::string& n, const std::string& b, const std::string& manu, float price, int q, const std::string& date)
: category(cat), name(n), brand(b), manufacturer(manu), purchasePrice(price), quantity(q), addDate(date) {}

Product::Product(const std::string& cat, const std::string& n, const std::string& b, int s, float p, float purchaseP)
: category(cat), name(n), brand(b), stock(s), price(p), purchasePrice(purchaseP) {}

// 读取并验证日期格式的函数    
std::string readDate(const std::string& prompt) {
	std::regex datePattern(R"(\d{4}-\d{2}-\d{2})"); // YYYY-MM-DD格式
	std::string inputDate;
	bool valid = false;
	
	do {
		std::cout << prompt;
		std::cin >> inputDate;
		if (std::cin.fail() || !std::regex_match(inputDate, datePattern)) {
			std::cout << "日期格式不正确，请使用YYYY-MM-DD格式重新输入。\n";
			std::cin.clear(); // 清除错误标志
			// 忽略当前行的剩余输入，直到遇到换行符
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		} else {
			valid = true;
		}
	} while (!valid);
	
	return inputDate;
}
// 字符串读取函数
std::string readString(const std::string& prompt) {
	std::string input;
	std::cout << prompt;
	// 只在前面的输入确实有剩余换行符时忽略
	if (std::cin.peek() == '\n') {
		std::cin.ignore();
	}
	std::getline(std::cin, input);
	return input;
}

// 整数读取函数
int readInt(const std::string& prompt) {
	int value;
	while (true) {
		std::cout << prompt;
		if (std::cin >> value) {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 清除可能存在的换行符
			return value;
		} else {
			std::cout << "请输入一个有效的整数。\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// 清除可能存在的换行符
		}
	}
}
// 浮点数读取函数
double readDouble(const std::string& prompt) {
	double value;
	while (true) {
		std::cout << prompt;
		if (std::cin >> value) {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 清除可能存在的换行符
			return value;
		} else {
			std::cout << "请输入一个有效的数字。\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// 清除可能存在的换行符
		}
	}
}
// Manager类中的函数实现
void Manager::addProduct() {
	std::string name = readString("请输入产品名称: ");
	std::string category = readString("请输入产品类别(食品、化妆品、日用品和饮料): ");
	std::string brand = readString("请输入产品品牌: ");	
	
	// 查找库存中是否已存在该商品
	auto it = std::find_if(products.begin(), products.end(), [&](const Product& product) {
		return product.category == category && product.name == name && product.brand == brand;
	});
	
	if (it != products.end()) {// 如果找到了，增加库存数量
		std::cout<<"此商品在库存记录中，";
		double purchasePrice = it->purchasePrice;
		double price = it->price;
		std::string manufacturer = readString("请输入生产厂家: ");	
		int quantity = readInt("请输入进货数量: ");	
		std::string purchaseDate = readDate("请输入购买日期 (YYYY-MM-DD): ");
		it->stock += quantity;
		std::cout << "商品【"<<name<<"("<<brand<<")】库存增加成功! 当前库存量: " << it->stock << std::endl;
		PurchaseRecord newPurchase(category, name, brand, manufacturer, purchasePrice, quantity, purchaseDate);
		purchases.push_back(newPurchase);
	} 
	else {// 如果没有找到，添加新的商品到库存中
		std::cout << "未添加过该商品,";
		double purchasePrice = readDouble("请输入产品进价(元): ");
		double price = readDouble("请输入产品定价(元): ");
		std::string manufacturer = readString("请输入生产厂家: ");	
		int quantity = readInt("请输入进货数量: ");	
		std::string purchaseDate = readDate("请输入购买日期 (YYYY-MM-DD): ");
		Product newProduct(category, name, brand, quantity, price, purchasePrice);
		products.push_back(newProduct);
		std::cout << "新的商品【"<<name<<"("<<brand<<")】已成功添加到库存中!"<<std::endl;
		PurchaseRecord newPurchase(category, name, brand, manufacturer, purchasePrice, quantity, purchaseDate);
		purchases.push_back(newPurchase);
	}
}

void Manager::sellProduct() {
	std::string category = readString("请输入商品种类(食品、化妆品、日用品和饮料): ");
	std::string name = readString("请输入商品名称: ");
	std::string brand = readString("请输入商品品牌: "); 
	
	// 查找商品
	auto it = std::find_if(products.begin(), products.end(), [&](const Product& product) {
		return product.category == category && product.name == name && product.brand == brand;
	});
	
	if (it == products.end()) {
		std::cout << "商品不存在" << std::endl;
	} else {
		int quantity = readInt("请输入出售数量: ");
		
		// 商品存在且库存足够
		if (it->stock >= quantity) {
			// 更新库存
			it->stock -= quantity;
			
			// 计算利润
			double profit = (it->price - it->purchasePrice) * quantity; // 利润计算公式：(售价 - 进价) * 数量
			
			// 记录出售日期
			std::string saleDate = readDate("请输入销售日期: ");
			
			// 创建销售记录
			SaleRecord saleRecord(category, name, brand, quantity, profit, saleDate);
			sales.push_back(saleRecord);
			
			// 输出销售信息和利润
			std::cout <<"【"<<name<<"("<<brand<<")】出售成功, 利润为:" << profit <<"元, 剩余数量:" << it->stock << std::endl;
		} else {
			// 库存不足
			std::cout << "库存["<<it->stock<<"]不足，出库失败" << std::endl;
		}
	}
}

void Manager::searchProduct() {
	std::string category = readString("请输入商品种类(输入*代表所有): ");
	std::string name = readString("请输入商品名称(输入*代表所有): ");
	std::string brand = readString("请输入商品品牌(输入*代表所有): ");
	searchInventory(category, name, brand);
	searchPurchases(category, name, brand);
	searchSales(category, name, brand);
}

void Manager::editProduct() {
	std::string category = readString("请输入商品的种类(食品、化妆品、日用品和饮料)：");
	std::string name = readString("请输入商品的名称：");
	std::string brand = readString("请输入商品的品牌：");
	
	auto it = std::find_if(products.begin(), products.end(), [&](const Product& product) {
		return product.category == category && product.name == name && product.brand == brand;
	});
	
	if (it != products.end()) {
		std::cout << "找到商品【"<<name<<"("<<brand<<")】，现在您可以修改它的信息。" << std::endl;
		it->category = readString("请输入新的种类(食品、化妆品、日用品和饮料)：");
		it->name = readString("请输入新的名称：");
		it->brand = readString("请输入新的品牌：");
		it->stock = readInt("请输入新的库存：");
		it->price = readDouble("请输入新的售价(元)：");
		it->purchasePrice = readDouble("请输入新的进价(元)：");
	} else {
		std::cout << "未找到指定商品。" << std::endl;
	}
}

void Manager::displayStatistics() {
	// 输出所有库存
	std::cout << "\n=== 全部库存如下（按照库存量由大到小排列）===" << std::endl;
	std::sort(products.begin(), products.end()); // 使用Product结构体中定义的排序规则
	for (const auto& product : products) {
		std::cout << "种类: " << product.category
		<< ", 名称: " << product.name
		<< ", 品牌: " << product.brand
		<< ", 库存: " << product.stock
		<< ", 售价(元): " << product.price
		<< ", 进价(元): " << product.purchasePrice << std::endl;
	}
	
	// 输出所有进货记录
	std::cout << "\n=== 全部进货记录（按照日期排列）===" << std::endl;
	std::sort(purchases.begin(), purchases.end()); // 使用PurchaseRecord结构体中定义的排序规则
	for (const auto& purchase : purchases) {
		std::cout << "种类: " << purchase.category
		<< ", 名称: " << purchase.name
		<< ", 品牌: " << purchase.brand
		<< ", 进货厂家: " << purchase.manufacturer
		<< ", 进价(元): " << purchase.purchasePrice
		<< ", 数量: " << purchase.quantity
		<< ", 进货日期: " << purchase.addDate << std::endl;
	}
	
	// 输出所有销售记录
	std::cout << "\n=== 全部销售记录（按照日期排列）===" << std::endl;
	std::sort(sales.begin(), sales.end()); // 使用SaleRecord结构体中定义的排序规则
	for (const auto& sale : sales) {
		std::cout << "种类: " << sale.category
		<< ", 名称: " << sale.name
		<< ", 品牌: " << sale.brand
		<< ", 数量: " << sale.quantity
		<< ", 总利润: " << sale.totalProfit
		<< ", 销售日期: " << sale.saleDate << std::endl;
	}
}

void Manager::deleteProduct() {
	std::string category = readString("请输入商品的种类(食品、化妆品、日用品和饮料)：");
	std::string name = readString("请输入商品的名称：");
	std::string brand = readString("请输入商品的品牌：");
	
	auto new_end = std::remove_if(products.begin(), products.end(), [&](const Product& product) {
		return product.category == category && product.name == name && product.brand == brand;
	});
	
	if (new_end != products.end()) {
		products.erase(new_end, products.end());
		std::cout << "商品【"<<name<<"("<<brand<<")】已被成功删除。" << std::endl;
	} else {
		std::cout << "未找到指定商品，删除失败。" << std::endl;
	}
}

void Manager::displayprofit() {
	std::string startDate = readDate("请输入统计开始日期(YYYY-MM-DD):");
	std::string endDate = readDate("请输入统计结束日期(YYYY-MM-DD):");
	
	// 用于每种商品的总利润
	std::map<std::string, double> productProfits;
	// 用于存储每类商品的总利润
	std::map<std::string, double> categoryProfits = {
		{"食品", 0.0},
		{"化妆品", 0.0},
		{"日用品", 0.0},
		{"饮料", 0.0}
	};
	
	// 筛选并计算利润
	for (const auto& sale : sales) {
		if (sale.saleDate >= startDate && sale.saleDate <= endDate) {
			std::string productKey = sale.category + ":" + sale.name + ":" + sale.brand;
			productProfits[productKey] += sale.totalProfit;
			categoryProfits[sale.category] += sale.totalProfit;
		}
	}
	
	// 排序并输出每种商品的利润
	std::vector<std::pair<std::string, double>> sortedProductProfits(productProfits.begin(), productProfits.end());
	std::sort(sortedProductProfits.begin(), sortedProductProfits.end(),
		[](const auto& a, const auto& b) { return a.second > b.second; });
	
	std::cout << "\n=== 统计时间内每种商品的利润 ===" << std::endl;
	for (const auto& profit : sortedProductProfits) {
		if (profit.second > 0) {
			std::cout << profit.first << " - 利润: " << std::fixed << std::setprecision(2) << profit.second << std::endl;
		}
	}
	
	// 排序并输出每类商品的总利润
	std::vector<std::pair<std::string, double>> sortedCategoryProfits(categoryProfits.begin(), categoryProfits.end());
	std::sort(sortedCategoryProfits.begin(), sortedCategoryProfits.end(),
		[](const auto& a, const auto& b) { return a.second > b.second; });
	
	std::cout << "\n=== 统计时间内四类商品的总利润 ===" << std::endl;
	for (const auto& profit : sortedCategoryProfits) {
		std::cout << profit.first << " - 总利润: " << std::fixed << std::setprecision(2) << profit.second << std::endl;
	}
}

void Manager::searchInventory(const std::string& category, const std::string& name, const std::string& brand) {
	std::vector<Product> filtered;
	
	// 遍历库存并筛选
	for (const auto& product : products) {
		if ((category == "*" || product.category == category) &&
			(name == "*" || product.name == name) &&
			(brand == "*" || product.brand == brand)) {
			filtered.push_back(product);
		}
	}
	
	// 根据库存数量进行排序
	std::sort(filtered.begin(), filtered.end());
	
	std::cout << "\n=== 库存查询结果 ===" << std::endl;
	
	if (filtered.empty()) {
		std::cout << "该商品库存信息不存在。" << std::endl;
	} else {
		for (const auto& item : filtered) {
			std::cout << "分类：" << std::setw(10) << std::left << item.category
			<< "名称：" << std::setw(15) << item.name
			<< "品牌：" << std::setw(14) << item.brand
			<< "库存数量：" << std::setw(6) << item.stock
			<< "价格(元)：" << std::setw(8) << item.price
			<< "进价(元)：" << std::setw(8) << item.purchasePrice
			<< std::endl;
		}
	}
}

void Manager::searchPurchases(const std::string& category, const std::string& name, const std::string& brand) {
	std::vector<PurchaseRecord> filtered;
	
	for (const auto& purchase : purchases) {
		if ((category == "*" || purchase.category == category) &&
			(name == "*" || purchase.name == name) &&
			(brand == "*" || purchase.brand == brand)) {
			filtered.push_back(purchase);
		}
	}
	
	std::sort(filtered.begin(), filtered.end());
	
	std::cout << "\n=== 进货记录查询结果 ===" << std::endl;
	
	if (filtered.empty()) {
		std::cout << "该入库信息不存在。" << std::endl;
	} else {
		for (const auto& item : filtered) {
			std::cout << "分类：" << std::setw(10) << std::left << item.category
			<< "名称：" << std::setw(15) << item.name
			<< "品牌：" << std::setw(14) << item.brand
			<< "制造商：" << std::setw(12) << item.manufacturer
			<< "进价(元)：" << std::setw(8) << item.purchasePrice
			<< "数量：" << std::setw(6) << item.quantity
			<< "添加日期：" << std::setw(10) << item.addDate
			<< std::endl;
		}
	}
}

void Manager::searchSales(const std::string& category, const std::string& name, const std::string& brand) {
	std::vector<SaleRecord> filtered;
	
	for (const auto& sale : sales) {
		if ((category == "*" || sale.category == category) &&
			(name == "*" || sale.name == name) &&
			(brand == "*" || sale.brand == brand)) {
			filtered.push_back(sale);
		}
	}
	
	std::sort(filtered.begin(), filtered.end());
	
	std::cout << "\n=== 销售记录查询结果 ===" << std::endl;
	
	if (filtered.empty()) {
		std::cout << "该出货信息不存在。" << std::endl;
	} else {
		for (const auto& item : filtered) {
			std::cout << "分类：" << std::setw(10) << std::left << item.category
			<< "名称：" << std::setw(15) << item.name
			<< "品牌：" << std::setw(14) << item.brand
			<< "数量：" << std::setw(6) << item.quantity
			<< "总利润：" << std::setw(10) << item.totalProfit
			<< "销售日期：" << std::setw(10) << item.saleDate
			<< std::endl;
		}
	}
}

void Manager::saveToFile() {
	// 保存产品库存信息
	std::ofstream productFile("products.txt");
	
	if (productFile.is_open()) {
		for (const auto& product : products) {
			productFile << product.category << ","
			<< product.name << ","
			<< product.price << ","
			<< product.stock << ","
			<< product.brand << ","
			<< product.purchasePrice << std::endl;
		}
		productFile.close();
		std::cout << "商品库存信息保存成功!" << std::endl;
	} else {
		std::cerr << "商品库存信息保存失败" << std::endl;
	}
	
	// 保存销售记录信息
	std::ofstream saleFile("SaleRecords.txt");
	
	if (saleFile.is_open()) {
		for (const auto& sale : sales) {
			saleFile << sale.category << ","
			<< sale.name << ","
			<< sale.brand << ","
			<< sale.quantity << ","
			<< sale.saleDate << ","
			<< sale.totalProfit << std::endl;
		}
		saleFile.close();
		std::cout << "销售记录保存成功!" << std::endl;
	} else {
		std::cerr << "销售记录保存失败" << std::endl;
	}
	
	// 保存进货信息
	std::ofstream purchaseFile("PurchaseRecords.txt");
	
	if (purchaseFile.is_open()) {
		for (const auto& purchase : purchases) {
			purchaseFile << purchase.category << ","
			<< purchase.name << ","
			<< purchase.brand << ","
			<< purchase.manufacturer << ","
			<< purchase.purchasePrice << ","
			<< purchase.quantity << ","
			<< purchase.addDate << std::endl;
		}
		purchaseFile.close();
		std::cout << "进货记录保存成功!" << std::endl;
	} else {
		std::cerr << "进货记录保存失败" << std::endl;
	}
}

void Manager::loadFromFile(){
	// 商品库存信息
	std::ifstream fileProducts("products.txt");
	std::string lineProducts;
	
	if (fileProducts.is_open()) {
		while (getline(fileProducts, lineProducts)) {
			std::stringstream linestream(lineProducts);
			std::string category, name, brand;
			float price, purchasePrice;
			int stock;
			getline(linestream, category, ',');
			getline(linestream, name, ',');
			linestream >> price;
			linestream.ignore();
			linestream >> stock;
			linestream.ignore();
			getline(linestream, brand, ',');
			linestream >> purchasePrice;
			products.emplace_back(category, name, brand, stock, price, purchasePrice);
		}
		fileProducts.close();
		std::cout << "商品库存信息读取成功！" << std::endl;
	} else {
		std::cerr << "无法打开商品库存信息文件" << std::endl;
	}
	
	// 销售记录
	std::ifstream fileSales("SaleRecords.txt");
	std::string lineSales;
	
	if (fileSales.is_open()) {
		while (getline(fileSales, lineSales)) {
			std::stringstream linestream(lineSales);
			std::string category, name, brand, saleDate;
			int quantity;
			double totalProfit;
			getline(linestream, category, ',');
			getline(linestream, name, ',');
			getline(linestream, brand, ',');
			linestream >> quantity;
			linestream.ignore();
			getline(linestream, saleDate, ',');
			linestream >> totalProfit;
			sales.emplace_back(category, name, brand, quantity, totalProfit, saleDate);
		}
		fileSales.close();
		std::cout << "销售记录读取成功！" << std::endl;
	} else {
		std::cerr << "无法打开销售记录文件" << std::endl;
	}
	
	// 进货记录
	std::ifstream filePurchases("PurchaseRecords.txt");
	std::string linePurchases;
	
	if (filePurchases.is_open()) {
		while (getline(filePurchases, linePurchases)) {
			std::stringstream linestream(linePurchases);
			std::string category, name, brand, manufacturer, addDate;
			float purchasePrice;
			int quantity;
			getline(linestream, category, ',');
			getline(linestream, name, ',');
			getline(linestream, brand, ',');
			getline(linestream, manufacturer, ',');
			linestream >> purchasePrice;
			linestream.ignore();
			linestream >> quantity;
			linestream.ignore();
			getline(linestream, addDate);
			purchases.emplace_back(category, name, brand, manufacturer, purchasePrice, quantity, addDate);
		}
		filePurchases.close();
		std::cout << "进货记录读取成功！" << std::endl;
	} else {
		std::cerr << "无法打开进货记录文件" << std::endl;
	}
}


