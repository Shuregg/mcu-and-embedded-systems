#pragma once

#define TOGGLE_BIT(REG, MASK) \
    REG ^= MASK;
    
void myled_enable();
void myled_toggle();
void myled_disable();