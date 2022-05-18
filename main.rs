enum Commande{
    echo,
    mv,
    mkdir,
    rm,
    kill,
    kill -s,
    ls,
    tee,
    cat,
    grep,
    grep -i,
    grep -v,
    grep -v -i,
    grep -i -v

}

fn main(arg : &str) {
    println!("{:?}", arg);
}