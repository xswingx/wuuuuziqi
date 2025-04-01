#include "qipan.h"
#include<QPainter>
#include<QDebug>
#include<QMessageBox>

QiPan::QiPan(QWidget *parent) :
    QWidget(parent),
    m_hoverRow(-1),
    m_hoverCol(-1),
    m_hoverFlag(false)

{
    /* 初始化清空棋盘*/
    for(int idx = 0;idx < m_boardSize;idx++){
        for(int jdx = 0;jdx < m_boardSize;jdx++){
            m_board[idx][jdx] = EMPTY;
        }
    }
    /*设置鼠标追踪*/
    setMouseTracking(true);
}


/*绘画事件 */
void QiPan::paintEvent(QPaintEvent *event)
{
    /*创建画家类*/
    QPainter painter(this);

    /*去除毛刺——抗锯齿*/
    painter.setRenderHint(QPainter::Antialiasing);

    /* 设置棋盘背景颜色 */
    QColor background =QColor(118,104,154); //淡灰色
    painter.fillRect(rect(),background);

    /*绘制棋盘*/
    for(int idx = 0;idx < m_boardSize; idx++){
        /*绘制竖线*/
        painter.drawLine(m_margin + idx * m_cellSize,
                         m_margin,
                         m_margin + idx * m_cellSize,
                         m_margin + (m_boardSize - 1) * m_cellSize);
        /*绘制横线*/
        painter.drawLine(m_margin,
                         m_margin + idx * m_cellSize,
                         m_margin +(m_boardSize - 1) * m_cellSize,
                         m_margin + idx * m_cellSize);
        /*绘制悬停点*/
        if(m_hoverFlag == true &&
          (m_hoverRow >= 0 && m_hoverRow < m_boardSize) &&
          (m_hoverCol >= 0 && m_hoverCol < m_boardSize) &&
          m_board[m_hoverRow][m_hoverCol] ==EMPTY)
        {
            /*设置笔刷*/
            painter.setBrush(Qt::red);

            painter.drawEllipse(QPoint(m_margin + m_hoverRow * m_cellSize,m_margin +m_hoverCol * m_cellSize),
                                m_cellSize / 6,m_cellSize / 6);

        }
    }

    /*绘制棋子*/
    for(int row = 0;row < m_boardSize;row++){
        for(int col = 0;col < m_boardSize;col++){
            /*玩家*/
            if(m_board[row][col] == PLAYER)
            {
                /*设置笔刷*/
                painter.setBrush(Qt::black);
                painter.drawEllipse(QPoint(m_margin + row * m_cellSize,m_margin +col * m_cellSize),
                                    m_cellSize / 3,m_cellSize / 3);
            }
            /*人机*/
            else if(m_board[row][col] == COPUTER)
            {
                /*设置笔刷*/
                painter.setBrush(Qt::white);
                painter.drawEllipse(QPoint(m_margin + row * m_cellSize,m_margin +col * m_cellSize),
                                    m_cellSize / 3,m_cellSize / 3);
            }
        }
    }
}


/*鼠标移动事件*/
void QiPan::mouseMoveEvent(QMouseEvent *event)
{
    int row = (event->x() - m_margin + m_cellSize / 2) / m_cellSize;
    int col = (event->y() - m_margin + m_cellSize / 2) / m_cellSize;

    if((row >= 0 && row < m_boardSize) && (col >= 0 && col < m_boardSize))
    {
        if(m_hoverRow != row || m_hoverCol != col)
        {
            m_hoverRow=row;
            m_hoverCol=col;
            m_hoverFlag =true;
            /*手动触发绘画事件*/
            update();
        }

    }
    else
    {
        /*不在棋盘的时候，清空悬停点的坐标*/
        m_hoverFlag=false;
        m_hoverRow =m_hoverCol =-1;
        update();
    }
}


/*鼠标点击事件*/
void QiPan::mousePressEvent(QMouseEvent *event)
{
    int row = (event->x() - m_margin + m_cellSize / 2) / m_cellSize;
    int col = (event->y() - m_margin + m_cellSize / 2) / m_cellSize;

    /*判断鼠标点击是否在棋盘内部*/
    if((row >= 0 && row < m_boardSize) &&
       (col >=0 && col < m_boardSize) &&
       m_board[row][col] == EMPTY)
    {
        if(m_Color == 0)
        {
            /*插入数据*/
            m_board[row][col] = PLAYER;

            /*手动更新绘画事件*/
            update();

            /*判断谁获胜*/
            bool res = isCheckWin(row,col,PLAYER);
            if(res == true){
                QMessageBox::information(this,"游戏结束","黑子获胜");
            }
            m_Color = 1;
        }
        else
        {
            /*插入数据*/
            m_board[row][col] = COPUTER;

            /*手动更新绘画事件*/
            update();

            /*判断谁获胜*/
            bool res = isCheckWin(row,col,COPUTER);
            if(res == true){
                QMessageBox::information(this,"游戏结束","白子获胜");
            }
            m_Color = 0;
        }
    }
}

/*判断用户是否获胜*/
bool QiPan::isCheckWin(int row,int col,ROLE role)
{
    int cnt1 = 1,cnt2 = 1,cnt3 = 1,cnt4 = 1;
    for(int i=row+1;i<m_boardSize;i++){
        if(m_board[i][col]==role){
            cnt1++;
        }else{
            break;
        }
    }
    for(int i=row-1;i>=0;i--){
        if(m_board[i][col]==role){
            cnt1++;
        }else{
            break;
        }
    }
    if(cnt1>=5){
        return true;
    }

    for(int i=col+1;i<m_boardSize;i++){
        if(m_board[row][i]==role){
            cnt2++;
        }else{
            break;
        }
    }
    for(int i=col-1;i>=0;i--){
        if(m_board[row][i]==role){
            cnt2++;
        }else{
            break;
        }
    }
    if(cnt2>=5){
        return true;
    }

    for(int i=1;row+i<m_boardSize&&col+i<m_boardSize;i++){
        if(m_board[row+i][col+i]==role){
            cnt3++;
        }else{
            break;
        }
    }
    for(int i=1;row-i>=0&&col-i>=0;i++){
        if(m_board[row-i][col-i]==role){
            cnt3++;
        }else{
            break;
        }
    }
    if(cnt3>=5){
        return true;
    }

    for(int i=1;row+i<m_boardSize&&col-i>=0;i++){
        if(m_board[row+i][col-i]==role){
            cnt4++;
        }else{
            break;
        }
    }
    for(int i=1;row-i>=0&&col+i<m_boardSize;i++){
        if(m_board[row-i][col+i]==role){
            cnt4++;
        }else{
            break;
        }
    }
    if(cnt4>=5){
        return true;
    }
    return false;
}
