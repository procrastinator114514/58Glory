import pygame
import sys

pygame.init()
screen = pygame.display.set_mode((800, 600))
clock = pygame.time.Clock()
font = pygame.font.Font("C:/Windows/Fonts/simhei.ttf", 28)

class OptionSelector:
    def __init__(self, label, options, pos):
        self.label = label            # 显示的文字
        self.options = options        # 选项列表
        self.index = 0                # 当前选中项索引
        self.pos = pos                # (x, y)
        self.left_rect = pygame.Rect(pos[0] + 150, pos[1], 40, 40)
        self.right_rect = pygame.Rect(pos[0] + 310, pos[1], 40, 40)

    def draw(self, surface):
        # 标题
        label_text = font.render(f"{self.label}：", True, (0, 0, 0))
        surface.blit(label_text, self.pos)

        # 当前选项
        current = self.options[self.index]
        option_text = font.render(current, True, (0, 0, 0))
        surface.blit(option_text, (self.pos[0] + 210, self.pos[1] + 5))

        # 左按钮
        pygame.draw.rect(surface, (200, 200, 200), self.left_rect)
        pygame.draw.polygon(surface, (0, 0, 0), [
            (self.left_rect.centerx + 10, self.left_rect.centery - 10),
            (self.left_rect.centerx - 10, self.left_rect.centery),
            (self.left_rect.centerx + 10, self.left_rect.centery + 10)
        ])

        # 右按钮
        pygame.draw.rect(surface, (200, 200, 200), self.right_rect)
        pygame.draw.polygon(surface, (0, 0, 0), [
            (self.right_rect.centerx - 10, self.right_rect.centery - 10),
            (self.right_rect.centerx + 10, self.right_rect.centery),
            (self.right_rect.centerx - 10, self.right_rect.centery + 10)
        ])

    def handle_event(self, event):
        if event.type == pygame.MOUSEBUTTONDOWN:
            if self.left_rect.collidepoint(event.pos):
                self.index = (self.index - 1) % len(self.options)
            elif self.right_rect.collidepoint(event.pos):
                self.index = (self.index + 1) % len(self.options)

    def get_value(self):
        return self.options[self.index]

# 创建多个选项条
selectors = [
    OptionSelector("音量", ["低", "中", "高", "极高"], (150, 100)),
    OptionSelector("难度", ["简单", "普通", "困难"], (150, 180)),
    OptionSelector("语言", ["中文", "英文", "日文"], (150, 260)),
]

while True:
    screen.fill((255, 255, 255))

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()
        for selector in selectors:
            selector.handle_event(event)

    # 绘制所有选项条
    for selector in selectors:
        selector.draw(screen)

    pygame.display.flip()
    clock.tick(60)
