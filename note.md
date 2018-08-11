二分查找
	mid = L + (R - L) / 2
	LowerBound(int a[], int size, int p); 小于p的最大值的下标
	二分法求方程的根，每次减少查找区间一半
	例题1   查找要快，让待查找的数据有序
		二分查找
			排序 nlogn
			每个元素a[i]查找(m-a[i]) nlogn
		贪心表
			排序 nlogn
			设置i = 0, j = n-1
			while(a[i]+a[j] != n){
				if(a[i]+a[j]>m) j--;
				if(a[i)+a[j]<m) i++;
			}
	例题2  百练 2456
分治
	归并排序
	快速排序
	例题：输出前m大的数
		将问题分解为两部分，分别处理两部分 -> O(nlogn)
		将问题分解为两部分，只处理一部分   -> O(n)
	例题：求排序的逆序数
		O(n2) -> O(nlogn)
贪心
	圣诞老人的礼物
		如果只能整箱拿，就不能用贪心
	看电影
	Stall Reservations
		
动态规划
	数字三角形
	最长上升子序列 为什么不能贪心
	最长公共子序列
	最佳加法表达式
	神奇的口袋（基础背包）
	01背包
	滑雪
	方盒游戏（动规升维）
	灌溉草场 qj
	海贼王之伟大航路（状态压缩）
	课程大作业（状态压缩 路径记录）
	炮兵阵地（三维 state进一步状态压缩）
深搜
	搜索的复杂度不好估计
	遍历
		void dfs(v){
			visit(v); // 标记
			for each u of v{ // 遍取
				if(!visit(u)){ // 避免重复访问
					dfs(v);
				}
			}
		}
	寻找路径（遍历的时候记录路径）
		int depth;
		void dfs(v){
			visit(v); // 标记
			for each u of v{ // 遍取
				depth++;
				if(!visit(u)){ // 避免重复访问
					dfs(v);
				}
				depth--;
			}
			unvisit(v); // 标记为新点，使得其他路径可以访问该点
		}
		void dfs(v, depth){
			visit(v); // 标记
			for each u of v{ // 遍取
				if(!visit(u)){ // 避免重复访问
					dfs(v, depth+1);
				}
			}
			unvisit(v); // 标记为新点
		}
	寻找最短路径（最优性剪枝）
	
	图的表示法
		邻接矩阵 遍历复杂度O(n^2)
		邻接表 遍历复杂度O(n+e)
	
	寻路问题：
	生日蛋糕：
		搜索顺序：如果搜索顺序是任意的，从分支少的开始搜索
		最优性剪枝 记录全局最小面积
		预测最优性剪枝 按最节省的方式来搭，表面积比最优解大
 		可行性剪枝（预测）体积 半径 高度
		保存结果避免重复计算
		break循环
广搜
	抓住那头牛
	迷宫问题
	迷宫问题变形（拯救行动）
	迷宫问题变形（鸣人和佐助）
	迷宫问题变形（Saving Tang Monk）
	八数码问题
	
	搜索什么：状态定义。（如果状态不是数值，还需要状态编码；如果数值稀疏但是过大，还需要状态压缩）
	怎么扩展：状态转移——从一个*状态转移*到可达的其他状态。
	          怎么知道一个状态可以到哪些状态呢？
			  图：如果把状态抽象为结点，图上的相邻结点就是可到的状态。这是最抽象的模型，所有问题都可以转化为图的模型。
			  迷宫：上下左右的可达坐标
	搜索范围：状态自然*定义域*（可以在搜索过程中进行剪枝）
	搜索顺序：如果是树型图搜索，从分支少的开始搜索，提高剪枝效率
	
	总结起来就是解决三个问题：状态定义、状态定义域、状态转移、状态判重
	还需要给定一个初始状态和结束状态，确定搜索的起点和终点
高级搜索
	A*
	迭代加深
	IDA*
	Alpha-Beta剪枝
最小生成树
	Prim
	Kruscal
最短路
	Dijkstra		单源	不含负权边
	Bellman-Ford	单源	可含负权边，可判负权环
	SPFA			单源	可含负权边，可判负权环
	Floyd			多源	可含负权边
Tarjan
	强连通分量
	割点
	桥
	无向图的点双连通分支
	无向图的边双连通分支
计算几何
	Vector(x, y)
		Vector +(Vector);
		Vector -(Vector);
		Vector *(double);
		double *(Vector);
		double ^(Vector);
		double length();
		Vector unit();
		double project(Vector);
	Point(x, y)
	Line(Point a, Point b)
	
	double dist(Point, Point);
	double dist(Point, Line);
	

	
	

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

	
	
	