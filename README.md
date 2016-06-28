# RayTrace 光线跟踪

## 一、	问题描述

### 1.	基本要求：

在自己设计的三维场景上实现一个简单的光线跟踪模型。核心功能必须自己实现，禁止直接或间接使用任何显卡相关的功能帮助绘制（opengl、 direct3D、Java3d、渲染引擎等），禁止使用任何计算几何算法库帮助求交，如Open Mesh、CGAL、VTK、MeshLab等

### 2.	扩展功能：

-	抗锯齿效果（超采样）
-	物体求交加速（k-d tree、octree、层次包围盒等）
-	复杂网格模型/场景（模型读写，法向插值等）
-	多样化的材质效果（玻璃、金属等）
-	贴图（UV映射、凹凸贴图等）
-	软阴影（面光源采样）
-	景深（模拟相机光圈效果）
-	……

## 二、	编译和运行环境

- 编程语言：C++
- 编译工具：Visual Studio 2012
- 运行环境：Windows 10
- 其他信息：使用了opencv来帮助显示和保存图片，opencv版本为3.0.0

## 三、	算法和功能

本程序实现了两种原理的图像渲染算法

- 光线跟踪（ray tracing）：若不在all.h里加上#define PATHTRACING，则使用光线跟踪算法，计算了物体的漫反射、高光、镜面反射和折射（透射）

- 路径跟踪（path tracing）：若在all.h里加上#define PATHTRACING，则使用路径跟踪算法

## 四、	本程序实现的扩展功能如下

- 利用超采样进行抗锯齿
- 利用面光源采样产生软阴影（分布式光线追踪）
- 结合蒙特卡罗方法产生粗糙镜面反射（分布式光线追踪）
- 分布式光线追踪加速（重要性采样）
- 复杂网格模型的输入（obj文件读入）
- 物体求交加速（提供两种方式供选择：包围盒或k-d tree）
- 基于UV映射的纹理贴图（平面贴图和球贴图）
- 多样化材质效果（玻璃、金属等）
- 模拟照相机光圈产生景深效果

## 五、	使用

- 在all.h进行全局各种参数的控制
	- 若#define PATHTRACING表示使用路径跟踪算法，否则使用光线跟踪算法
	- 若#define KD表示使用KD-tree对obj求交，否则使用包围盒
	- 若#define DEPTH_OF_FIELD表示启用景深效果
	- 若#define SUPERSAMPLING表示启用9倍超采样（不应与景深同时启用）
	- 若#define IMPORTANCE_SAMPLING表示启用重要性采样来加速分布式光线追踪
	- PTSAMP宏表示PATHTRACING算法的采样数，一般要到1000以上效果才合格
	- SAMPLE宏表示光线跟踪采样数
	- EPS宏表示一个很小的量
	- TRACEDEPTH宏表示光线跟踪递归深度
	- GRIDSIZE宏表示网格每个维度上的数量
	- GRIDSHIFT宏表示计算网格时的偏移量，数值上应该是log2(GRIDSIZE)
	- MAXLIGHT宏表示最大光源数量
	- PI宏表示圆周率

- 在scene.cpp的init()函数中描述场景，例如
	<pre>m_Primitive = new Primitive*[500000];
	// ground plane
	m_Primitive[0] = new PlanePrim( vector3( 0, 1, 0 ), 4.4f );
	m_Primitive[0]->setName( "plane" );
	m_Primitive[0]->getMaterial()->setReflection( 0.6f );
	m_Primitive[0]->getMaterial()->setSpecular(0.8f);
	m_Primitive[0]->getMaterial()->setRefraction( 0.0f );
	m_Primitive[0]->getMaterial()->setDiffuse( 1.0f );
	m_Primitive[0]->getMaterial()->setColor( Color( 0.3f, 0.3f, 0.3f ) );

	// light
	m_Primitive[1] = new Box( BoundingBox( vector3( -1, 4.8, 4 ), vector3( 2, 0.01f, 2 ) ) );
	m_Primitive[1]->Light( true );
	m_Primitive[1]->getMaterial()->setColor( Color( 1, 1, 1 ) );

	m_Primitives = 2;
	//some code here
	</pre>

- 在raytracer.cpp的HYF_render()函数里设置照相机、光圈和焦距，例如
	<pre>
	//some code here
	Camera c = Camera(vector3(0,0,-5),vector3(0,0,0),5.0,8.0,6.0,0.01);
	//构造函数,眼睛位置(0,0,-5)，看向(0,0,0)，眼到投影平面距离为5.0，投影平面宽和高分别为8.0和6.0，像素大小和三维坐标系比例为0.01
	c.setRV(0.1,9.0);//设置光圈大小0.1，眼到焦平面距离9.0
	//some code here
	</pre>
	

## 六、结果展示

- 光线追踪算法，3878.11s

	说明：这张图片无景深效果，有软阴影效果，并使用采样9倍的超采样进行抗锯齿。后面墙壁和右侧墙壁使用了不同的平面纹理进行UV贴图，右侧较近的球使用了大理石的球面纹理贴图，右侧较远的球采用了粗糙镜面反射效果，左侧的球为透射球，地面带有一定的反射成分，中间有龙（dragon.obj）和兔子（bunny.obj）两个模型文件，采用kd-tree加速对它们的求交。其中龙采用古董的材质，兔子采用纯金材质。

	![](http://i.imgur.com/vkQlZXr.png)
 
- 光线追踪算法，4475.6s

	说明：场景和参数同前一张，不同之处在于加入景深效果，聚焦在龙模型处，光圈较小

	![](http://i.imgur.com/azDhbUm.png)
 
- 光线追踪算法，4319.85s

	说明：场景和参数同前一张，同样聚焦在龙模型处，光圈较大，可与前一张对比

	![](http://i.imgur.com/Qv3aaZt.png)
 
- 光线追踪算法，4452.48s

	说明：场景和参数同前一张，不同之处在于改为聚焦在兔子模型处，光圈大小与上一张相同

	![](http://i.imgur.com/SboCLBa.png)
 
- 路径追踪算法，采样数2000*4，150791s 

	![](http://i.imgur.com/yfj3yft.png)

- 路径追踪算法，采样数60*4，4812.53s（以下图片为同一场景不同采样数的对比） 

	![](http://i.imgur.com/JfkTSFm.jpg)

- 路径追踪算法，采样数100*4，7748.56s  

	![](http://i.imgur.com/QcXNcNQ.jpg)

- 路径追踪算法，采样数800*4，46489.3s  

	![](http://i.imgur.com/3E1lPRl.png)

- 路径追踪算法，采样数2000*4，121525s  

	![](http://i.imgur.com/mxMNVlU.png)

### 【参考资料】

- 计算机图形学课件
- <http://www.flipcode.com/archives/Raytracing_Topics_Techniques-Part_1_Introduction.shtml>
- <http://www.kevinbeason.com/smallpt/>
