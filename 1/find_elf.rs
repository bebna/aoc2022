use std::fs::File;
use std::io::{self, BufRead};
use std::path::Path;

fn main() {
    let mut top: [u32; 3] = [0,0,0];
    let mut current_calories = 0;
    if let Ok(lines) = read_lines("./input.txt") {
        for line in lines {
            if let Ok(entry) = line {
                if entry.trim().is_empty() {
                    cmpr_and_set_top_three(&mut top, current_calories);
                    current_calories = 0;
                } else {
                    current_calories += entry.trim().parse::<u32>().unwrap();
                }
            }
        }
        // last check, if the last entries don't close with an empty line
        if current_calories > 0 {
            cmpr_and_set_top_three(&mut top, current_calories);
        }
    }
    println!("{:#?}", top);
    println!("{}", top[0]+top[1]+top[2]);
}

fn read_lines<P>(filename: P) -> io::Result<io::Lines<io::BufReader<File>>>
where P: AsRef<Path>, {
    let file = File::open(filename)?;
    Ok(io::BufReader::new(file).lines())
}

// handles checking if someelf got more than others
// and the down ranking of the others
fn cmpr_and_set_top_three(top:&mut [u32], current:u32) {
    let mut cal = current;
    for i in 0..top.len() {
        let entry = top[i];
        if entry < cal {
            top[i] = cal;
            cal = entry;
        }
    }
}
