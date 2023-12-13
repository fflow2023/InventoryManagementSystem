## 这是一个Cpp课程设计项目的工程文件,原题目如下:  

## 原作者为Flow(23neuqer)，可以参考和借鉴思路，但是请勿直接抄袭和复制源代码，否则后果自负！

### 题目20：库存管理系统设计

1. **问题描述**

    超市中商品分为四类，分别是食品、化妆品、日用品和饮料。每种商品都包含商品名称、价格、库存量和品牌等信息。定义一个管理类，主要完成对商品的销售、统计和简单管理。

2. **功能要求**

    - 进货功能：按要求添加相应商品的信息到库存中。添加进货日期、生产厂家、进货价等信息。
    - 出货功能：出货时，先输入商品类别，然后输入商品名称，并在库存中查找该商品的相关信息。如果有库存量，输入出货的数量、出货日期，计算销售额和利润。如果库存量不够，给出提示信息，结束出货。
    - 统计功能：输出当前库存中所有商品的总数及详细信息；能统计每种商品一周时间内的销售额和利润；能统计每类商品的一周时间内的销售额和利润。输出统计信息时，要按从大到小进行排序。
    - 商品简单管理功能：添加功能、查询功能、修改功能、删除功能、商品信息存盘、读出信息。

3. **问题的解决方案**

    根据系统功能要求，可以将问题解决分为以下步骤：
    - 应用系统分析，建立该系统的功能模块框图以及界面的组织和设计；
    - 分析系统中的各个实体及它们之间的关系；
    - 根据问题描述，设计系统的类层次；
    - 完成类层次中各个类的描述；
    - 完成类中各个成员函数的定义；
    - 完成系统的应用模块；
    - 功能调试；
    - 完成系统总结报告。
