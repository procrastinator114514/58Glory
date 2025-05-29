# This is a 58_Glory project class file for the use of creating characters.
# Copyright©2025 58_Glory, BukSeong et al. . Written by procrastinator114514.
# The type of math should be designed as: 神,巨,强,中,弱 to 0,1,2,3,4.
# The type of identity should be designed as: 5,5师，6，5外教，其他生，other to 0,1,2,3,4,5.

class Character:
    def __init__(self, name, hp, top, math, identity, weapon, skill):
        self.weapon = weapon
        self.top = top
        self.skill = skill
        self.identity = identity
        self.math = math
        self.hp = hp
        self.name = name

class BDM(Character):
    def __init__(self):