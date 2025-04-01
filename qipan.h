#ifndef QIPAN_H
#define QIPAN_H

#include <QWidget>
#include <QMouseEvent>
#include "stdshared.h"
class QiPan : public QWidget
{
    Q_OBJECT
public:
    explicit QiPan(QWidget *parent = nullptr);

protected:
    /*绘画事件 */
    void paintEvent(QPaintEvent *event) override;
    /*鼠标移动事件*/
    void mouseMoveEvent(QMouseEvent *event) override;
    /*鼠标点击事件*/
    void mousePressEvent(QMouseEvent *event) override;
signals:

public slots:

private:
    /*判断用户是否获胜*/
    bool isCheckWin(int row,int col,ROLE role);

private:
    /*棋盘的尺寸*/
    static const int m_boardSize = 15;
    /*每个方块格子的尺寸*/
    static const int m_cellSize = 40;
    /*棋盘距离边缘的距离*/
    static const int m_margin = 20;
    /*棋盘上的点*/
    ROLE m_board[m_boardSize][m_boardSize];
    /*判断到轮到黑子还是白子*/
    int m_Color = 0;
    /* 悬停点坐标*/
    int m_hoverRow;
    int m_hoverCol;
    /*是否需要绘制悬停点*/
    bool m_hoverFlag;
};

#endif // QIPAN_H
