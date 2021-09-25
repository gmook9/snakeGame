class cell {
     public:
        cell();
        cell(int row, int col);

        bool &NotMunchie();
        bool &Munchie();

        int index();
        void creatIndex(int);

    private:
        bool _Munchie;
        int row, col;
        int _index;


};


