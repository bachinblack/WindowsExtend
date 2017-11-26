#ifndef IWIDGET_H
#define IWIDGET_H


class IWidget
{
public:
    virtual IWidget();
    virtual ~IWidget();
    virtual bool start();
    virtual void stop();

private:
    virtual void init();
};

class AWidget : public IWidget
{
public:
    AWidget();
    virtual ~AWidget();
    bool start;
    bool stop;

private:
    void init();
}

#endif // IWIDGET_H
