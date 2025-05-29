# This is a 58_Glory project syntax file for the use of creating a dropdown box.
# Copyright©2025 58_Glory, BukSeong et al. . Written by procrastinator114514.
# Warning. This syntax is not used in main file.

def draw_dropdown(options):  # This is the 下拉框 controller's default drawing syntax.
    # 外框
    pygame.draw.rect(screen, (200, 200, 200), (x, y, width, height))
    pygame.draw.rect(screen, (0, 0, 0), (x, y, width, height), 2)

    # 当前选中项
    text = font.render(selected_option, True, (0, 0, 0))
    screen.blit(text, (x + 10, y + 5))

    # 下拉箭头
    pygame.draw.polygon(screen, (0, 0, 0),
                        [(x + width - 25, y + 15), (x + width - 10, y + 15), (x + width - 17, y + 25)])

    if dropdown_open:
        for i, option in enumerate(options):
            option_rect = pygame.Rect(x, y + height + i * option_height, width, option_height)
            pygame.draw.rect(screen, (240, 240, 240), option_rect)
            pygame.draw.rect(screen, (0, 0, 0), option_rect, 1)

            option_text = font.render(option, True, (0, 0, 0))
            screen.blit(option_text, (x + 10, y + height + i * option_height + 5))