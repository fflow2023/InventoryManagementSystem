#include <iostream>
#include "Manager.h"

int main() {
	Manager manager;
	manager.loadFromFile();
	
	int choice;
	do{
		std::cout << "\n";
		std::cout << "********************************************\n";
		std::cout << "*        库存管理系统                       *\n";
		std::cout << "********************************************\n";
		std::cout << "* 1. 添加商品             2. 销售商品       *\n";
		std::cout << "* 3. 修改商品             4. 删除商品 	  *\n";
		std::cout << "* 5. 查询商品             6. 统计商品       *\n";
		std::cout << "* 7. 计算利润             8. 保存并退出     *\n";
		std::cout << "*******************************************\n";
		std::cout << "请输入您的选择: ";
		std::cin >> choice;
		switch (choice) {
		case 1:
			manager.addProduct();
			break;
			
		case 2:
			manager.sellProduct();
			break;
			
		case 3:
			manager.editProduct();
			break;
			
		case 4:
			manager.deleteProduct();
			break;			
			
		case 5:
			manager.searchProduct();
			break;
			
		case 6:
			manager.displayStatistics();
			break;
			
		case 7:
			manager.displayprofit();
			break;
			
		case 8:
			manager.saveToFile(); // 确保退出前保存数据
			std::cout << "谢谢使用，再见！" << std::endl;
			return 0;
			
		default:
			std::cout << "无效选择，请重新输入。\n";
		}
	}while(choice != 9);
	return 0;
}

