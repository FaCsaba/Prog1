use rand::{thread_rng, Rng};

#[derive(Default, Clone, PartialEq, Eq)]
enum Object {
    Character,
    Fruit,
    BubbleGum,
    #[default]
    Nothing
}

impl std::fmt::Display for Object {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> Result<(), std::fmt::Error> {
        match self {
            Object::Character => write!(f, "{}", "🧍‍"),
            Object::Fruit => write!(f, "{}", "🍎"),
            Object::BubbleGum => write!(f, "{}", "🍬"),
            Object::Nothing => write!(f, "{}", "x ")
        }
    }
}

#[derive(Default)]
struct Board {
    size: (u8, u8),
    iteration: usize,
    position: usize,
    blocked_for: usize,
    collected_fruit: u8,
    objects: Vec<Object>
}

impl Board {
    fn new(size: (u8, u8), bubble_gum_amount: u8) -> Self {
        let size_len: usize = (size.0*size.1).into();
        let mut objects: Vec<Object> = vec![Object::Nothing; size_len];
        objects[0] = Object::Character;
        while objects.iter().fold(0, |acc, o| if o == &Object::Fruit {acc+1} else {acc}) != 5 {
            objects[thread_rng().gen_range(1..size_len)] = Object::Fruit;
        }
        while objects.iter().fold(0, |acc, o| if o == &Object::BubbleGum {acc+1} else {acc}) != bubble_gum_amount {
            if objects[thread_rng().gen_range(1..size_len)] != Object::Fruit {
                objects[thread_rng().gen_range(1..size_len)] = Object::BubbleGum;
            }
        }
        Board { objects, size, ..Board::default() }
    }

    fn game_loop(mut self) {
        loop {
            if self.collected_fruit == 5 {
                break;
            }
            println!("{}", &self);
            if self.blocked_for == 0 {
                match self.objects[self.position+1] {
                    Object::Nothing => {},
                    Object::Character => unreachable!(),
                    Object::Fruit => {self.collected_fruit += 1},
                    Object::BubbleGum => {self.blocked_for = 3; },
                }
                self.objects.swap(self.position, self.position+1);
                self.objects[self.position] = Object::Nothing;
                self.position += 1;
            } else {
                self.blocked_for -= 1;
            }
            self.iteration += 1;
            std::thread::sleep(std::time::Duration::from_millis(200));
        }
        println!("{}", &self);
        println!("Won the game in {} iterations!", self.iteration);
    }
}

impl std::fmt::Display for Board {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> Result<(), std::fmt::Error> {
        print!("{esc}[2J{esc}[1;1H", esc = 27 as char);
        println!("Fruits collected: {}; Iteration: {}", &self.collected_fruit, &self.iteration);
        for y in 0..self.size.1 {
            for x in 0..self.size.0 {
                write!(f, "{} ", self.objects[Into::<usize>::into(y*self.size.0+x)])?;
            }
            write!(f, "\n")?;
        }
        return Ok(())
    }
}

fn main() {
    let b = Board::new((10, 10), 0);
    b.game_loop();
}