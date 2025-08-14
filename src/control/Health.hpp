class Health {
public:
    Health(int initial_health);

    void decrease(int amount);
    int get_health() const;

private:
    int health;
};
