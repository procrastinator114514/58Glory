import matplotlib.pyplot as plt

# 创建10x10的点阵
def create_grid():
    fig, ax = plt.subplots(figsize=(12,12))
    ax.set_xlim(0, 11)
    ax.set_ylim(0, 11)
    ax.set_aspect('equal')
    ax.axis('off')
    
    points = {}
    counter = 1
    
    for y in range(9, -1, -1):  # 从上到下
        for x in range(1, 11):   # 从左到右
            if counter == 10 or counter == 91:  # 跳过编号10和91的点
                counter += 1
                continue
            points[counter] = (x, y+1)  # y+1是为了让点从1开始而不是0
            ax.plot(x, y+1, 'ko', markersize=8)
            ax.text(x, y+1+0.15, str(counter), ha='center', va='center', fontsize=8)
            counter += 1
    
    return fig, ax, points

# 连接两点的方法
def connect_points(ax, points, x, y, color='red'):
    if x not in points or y not in points:
        print(f"错误：点{x}或点{y}不存在！")
        return
    
    x_coords, y_coords = zip(points[x], points[y])
    ax.plot(x_coords, y_coords, color=color, linewidth=2)

def mark_points(ax, points, point_numbers, color='green', size=12):
    """
    在指定编号的点上添加彩色方框标记
    参数:
        ax: matplotlib的axes对象
        points: 存储点位置的字典
        point_numbers: 要标记的点编号列表
        color: 颜色 ('green' 或 'purple')
        size: 方框大小
    """
    if color not in ['green', 'purple']:
        color = 'green'  # 默认绿色
    
    for num in point_numbers:
        if num in points:
            x, y = points[num]
            # 绘制方框（使用矩形补丁）
            rect = plt.Rectangle((x-0.2, y-0.2), 0.4, 0.4, 
                                linewidth=2, edgecolor=color, 
                                facecolor='none', zorder=10)
            ax.add_patch(rect)
        else:
            print(f"警告: 点 {num} 不存在，跳过标记")

# 创建点阵
fig, ax, points = create_grid()

# 一般区域
s_n = [12,13,14,15,22,32,42,16,17,18,19,12,16,26,37,47,52,53,64,65,52,62,72,82,66,67,58,59,57,67,76,86,82,63,42,23,24,28,27,86,67,68]
e_n = [42,43,34,35,25,34,44,36,37,48,49,15,19,29,39,49,82,83,84,85,54,64,75,85,86,87,88,89,59,69,79,89,73,74,33,34,15,19,38,77,78,59]

# 中央区域
s_c = [34,44,54,64,34,35,36,37]
e_c = [37,47,57,67,64,65,66,67]

# 铁道区域
s_r = [1,1,20,1,16,9,20,41,100,100,92,59,81,81,82,85]
e_r = [9,81,9,12,6,19,19,42,20,89,100,60,92,82,92,95]

for i in range(0,len(s_n)):
    connect_points(ax,points,s_n[i],e_n[i],color='black')

for i in range(0,len(s_c)):
    connect_points(ax,points,s_c[i],e_c[i],color='blue')

for i in range(0,len(s_r)):
    connect_points(ax,points,s_r[i],e_r[i],color='red')

# 标记绿色方框的点（经济区）
mark_points(ax, points, [23, 78], color='green')

# 标记紫色方框的点（塔）
mark_points(ax, points, [19,49,52,82], color='purple')

plt.title('Map of Campus\' Glory')
plt.tight_layout()
plt.show()
