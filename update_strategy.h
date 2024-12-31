#ifndef UPDATE_STRATEGY_H
#define UPDATE_STRATEGY_H

class UpdateStrategy {
public:
    virtual void update(Field& field, double dt, double dx, double D) = 0;
    virtual ~UpdateStrategy() = default;
};

#endif // UPDATE_STRATEGY_H