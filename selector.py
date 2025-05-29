# This is a 58_Glory project syntax file for the use of creating a selection box.
# Copyright©2025 58_Glory, BukSeong et al. . Written by procrastinator114514.
# Warning. This syntax is not used in main file.

def draw_selector(choice, x, y, options, selected_options, number):
    # This is the 左右选择器 controller's default drawing syntax.

    # 按钮位置
    left_rect = pygame.Rect(x+150, y, 40, 40)
    right_rect = pygame.Rect(x+410, y, 40, 40)

    # 标题文字
    label = option_font.render(choice, True, (0, 0, 0))
    screen.blit(label, (x, y))  # 150, 250

    # 当前选项显示
    option_text = option_font.render(options[selected_options[number]], True, (0, 0, 0))
    screen.blit(option_text, (x + 220, y + 5))

    # 左右按钮
    pygame.draw.rect(screen, (200, 200, 200), left_rect)
    pygame.draw.rect(screen, (200, 200, 200), right_rect)
    pygame.draw.polygon(screen, (0, 0, 0), [(x + 170, y + 20), (x + 185, y + 10), (x + 185, y + 30)])  # <
    pygame.draw.polygon(screen, (0, 0, 0), [(x + 430, y + 20), (x + 415, y + 10), (x + 415, y + 30)])  # >