# This is a 58_Glory project basic file for the use of main user interface.
# Copyright©2025 58_Glory, BukSeong et al. . Written by procrastinator114514.

import pygame
import sys

pygame.init()
screen = pygame.display.set_mode((1200, 1013))
pygame.display.set_caption("58glory")
clock = pygame.time.Clock()
font = pygame.font.Font("simhei.ttf", 48)
option_font = pygame.font.Font("simhei.ttf", 32)

background = pygame.image.load("map_gauss.png").convert()
title = pygame.image.load("title_bg_transparent.png").convert()
# These below are global variables.
width, height = 100, 20
option_height = 20

# These are prepared for the shade between two interfaces.
fade_surface = pygame.Surface((1200, 1013))
fade_surface.fill((0, 0, 0))

# This is the selection for heros and their weapons. The rules, take the 10 at the front for an examole:
# main hero, his/her weapon, second hero, his/her weapon, and so on.
selectors = []
selected_options = []
# This is for the menu's selection.
selected_option = 0
# This is for the interfaces' mark. Details are on their syntaxes' marks.
current_state = 0
# This is for the price.
price = [(2, 2), (1, 1), (0, 2)]

options_characters = ["-", "Birdman", "LYJ", "581", "582", "583", "YR", "DXD", "Fakeflower", "SJK", "An", "Office",
                      "Drrra", "郑阁", "明月", "Yangtze", "142", "C-6", "C-7", "牛yeahyeah", "郭猴", "蒜", "QC",
                      "HJK", "WEV", "ZYS", "LQL"]
options_weapons = ["-", "M202", "RPG", "加特林"]
selection_name = ["A方主武将", "武器", "A方武将2", "武器", "A方武将3", "武器", "A方武将4", "武器", "A方武将5",
                  "武器", "B方主武将", "武器", "B方武将2", "武器", "B方武将3", "武器", "B方武将4", "武器",
                  "B方武将5", "武器"]


class OptionSelector:
    def __init__(self, label, options, x, y):
        self.label = label  # 显示的文字
        self.options = options  # 选项列表
        self.index = 0  # 当前选中项索引
        self.x = x
        self.y = y
        self.pos = (self.x, self.y)
        self.left_rect = pygame.Rect(x + 150, y, 40, 40)
        self.right_rect = pygame.Rect(x + 310, y, 40, 40)

    def draw(self, surface):
        # 标题
        label_text = font.render(f"{self.label}：", True, (0, 0, 0))
        surface.blit(label_text, (self.x - 100, self.y))

        # 当前选项
        current = self.options[self.index]
        option_text = font.render(current, True, (0, 0, 0))
        surface.blit(option_text, (self.x + 210, self.y + 5))

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
        return self.index


# This is used for creating cache for selectors.
for k in range(10):
    selectors.append(OptionSelector(selection_name[2 * k], options_characters, 150, 200 + 50 * k))
    selectors.append(OptionSelector(selection_name[2 * k + 1], options_weapons, 600, 200 + 50 * k))


def fade_transition(draw_from, draw_to, variate_from=None, variate_to=None):  # This is the 淡入淡出 syntax.
    # 淡出当前界面
    for alpha in range(0, 255, 15):
        if variate_from == None:
            draw_from()
        else:
            draw_from(variate_from)
        fade_surface.set_alpha(alpha)
        screen.blit(fade_surface, (0, 0))
        pygame.display.flip()
        pygame.time.delay(30)

    # 淡入目标界面
    for alpha in range(255, -1, -15):
        if variate_to == None:
            draw_to()
        else:
            draw_to(variate_from)
        fade_surface.set_alpha(alpha)
        screen.blit(fade_surface, (0, 0))
        pygame.display.flip()
        pygame.time.delay(30)


def draw_menu(selected_index):  # current_state:0
    screen.blit(background, (0, 0))
    screen.blit(title, (300, 100))
    options = ["单机", "联机", "退出"]
    for i, text in enumerate(options):
        color = (255, 0, 0) if i == selected_index else (0, 0, 0)
        img = font.render(text, True, color)
        screen.blit(img, (300, 500 + i * 60))


confirm_button = pygame.Rect(1000, 450, 100, 50)


def draw_selection():  # current_state:1
    screen.blit(background, (0, 0))
    tips = "单机模式请先阅读武将表，商定后在下面的选择框中选择。"
    img = font.render(tips, True, (0, 0, 0))
    screen.blit(img, (0, 100))
    for selector in selectors:
        selector.draw(screen)
    pygame.draw.rect(screen, (200, 200, 200), confirm_button)
    confirm = "确定"
    img2 = font.render(confirm, True, (0, 0, 0))
    screen.blit(img2, (1000, 450))


def draw_developing():  # current_state:2
    screen.fill((50, 50, 150))
    tips1 = "开发中，前面的区域等以后再来探索吧！"
    tips2 = "按Esc键退出！"
    img1 = font.render(tips1, True, (0, 0, 0))
    img2 = font.render(tips2, True, (0, 0, 0))
    screen.blit(img1, (150, 450))
    screen.blit(img2, (150, 550))


def draw_fighting():  # current_state:3
    screen.fill((50, 50, 150))
    img1 = font.render(str(money[1]), True, (0, 0, 0))
    screen.blit(img1, (150, 450))


def draw_error_selection():  # current_state:4
    screen.fill((255, 255, 255))
    img1 = font.render("选择不符合规定，请重新选择", True, (0, 0, 0))
    screen.blit(img1, (150, 450))


def judge_money():
    for selector in selectors:
        selected_options.append(selector.get_value())
    for i in range(20):
        if selected_options[i] == 0:
            return -1
    count = 0
    sum_a = 15
    sum_b = 15
    a_temp = []
    b_temp = []
    for i in range(5):
        a_temp.append(2*i)
        sum_a -= price[selected_options[2 * i + 1] - 1][1]
        if selected_options[2 * i + 1] == 1:
            count += 1
    if count > 1 or sum_a < 0 or len(tuple(a_temp)) < len(a_temp):
        return -1
    else:
        count = 0
        for i in range(5):
            b_temp.append(2*i+10)
            sum_b -= price[selected_options[2 * i + 11] - 1][1]
            if selected_options[2 * i + 11] == 1:
                count += 1
        if count > 1 or sum_b < 0 or len(tuple(b_temp)) < len(b_temp):
            return -1
    return sum_a, sum_b


money = [15, 15]

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()

        if current_state == 0:
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_UP:
                    selected_option = (selected_option - 1) % 3
                elif event.key == pygame.K_DOWN:
                    selected_option = (selected_option + 1) % 3
                elif event.key == pygame.K_RETURN or event.key == pygame.K_KP_ENTER:
                    if selected_option == 0:
                        fade_transition(draw_menu, draw_selection, selected_option, None)
                        current_state = 1
                    elif selected_option == 1:
                        fade_transition(draw_menu, draw_developing, selected_option, None)
                        current_state = 2
                    elif selected_option == 2:
                        pygame.quit()
                        sys.exit()
        elif current_state == 1:
            for selector in selectors:
                selector.handle_event(event)
            if event.type == pygame.MOUSEBUTTONDOWN:
                if confirm_button.collidepoint(event.pos):
                    money = judge_money()
                    if money != -1:
                        fade_transition(draw_selection, draw_fighting,None ,None)
                        current_state = 3
                    else:
                        current_state = 4
            if event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE:
                fade_transition(draw_selection, draw_menu, None, selected_option)
                current_state = 0
        elif current_state == 2:
            if event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE:
                fade_transition(draw_developing, draw_menu, None, selected_option)
                current_state = 0
        elif current_state == 4:
            if event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE:
                current_state = 1

    if current_state == 0:
        draw_menu(selected_option)
    elif current_state == 1:
        draw_selection()
    elif current_state == 2:
        draw_developing()
    elif current_state == 3:
        draw_fighting()
    elif current_state == 4:
        draw_error_selection()

    pygame.display.flip()
    clock.tick(60)
