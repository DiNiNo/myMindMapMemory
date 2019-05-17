#ifndef SCENEBUFFER_H
#define SCENEBUFFER_H


class SceneBuffer
{
public:
    SceneBuffer();

    void setSelectedKnot(int value);
    void setMoveStatusFlag(bool value);

    int getSelectedKnot();

    bool getStatusFlag();
    bool getMoveStatusFlag();
private:
    static int selectedKnot;

    static bool statusFlag;
    static bool moveStatusFlag;
};

#endif // SCENEBUFFER_H
