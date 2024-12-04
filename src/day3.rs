use std::fs::File;
use std::io::{BufRead, BufReader};

pub(crate) fn main(reader: BufReader<File>) -> (String, String) {
    fn parse(s: &String, i: &mut usize, c: Option<char>) -> Option<char> {
        let found = s.chars().nth(*i);
        if found.is_some() && (c.is_none() || found.unwrap() == c.unwrap()) {
            *i += 1;
            return found;
        }

        None
    }

    fn parse_char(s: &String, i: &mut usize, c: char) -> bool {
        parse(s, i, Some(c)).is_some()
    }

    fn parse_string(s: &String, i: &mut usize, find: &str) -> bool {
        for c in find.chars() {
            if !parse_char(s, i, c) {
                return false;
            }
        }

        true
    }

    fn parse_num(s: &String, i: &mut usize) -> Option<i32> {
        let start = *i;
        while s.chars().nth(*i)?.is_numeric() {
            *i += 1;
        }

        if start != *i {
            return Some(s[start..*i].parse::<i32>().unwrap());
        }

        None
    }

    let mut result = 0;
    let mut result_2 = 0;
    let mut mul_enabled = true;
    for line in reader.lines() {
        let line = line.unwrap();

        for mut i in 0..line.len() {
            if parse_string(&line, &mut i, "do") {
                if parse_string(&line, &mut i, "()") {
                    mul_enabled = true;
                    continue;
                }

                if parse_string(&line, &mut i, "n't()") {
                    mul_enabled = false;
                    continue;
                }

                continue;
            }

            if !parse_string(&line, &mut i, "mul(") {
                continue;
            }

            let first_num = parse_num(&line, &mut i);
            if first_num.is_none() {
                continue;
            }

            if !parse_char(&line, &mut i, ',') {
                continue;
            }

            let second_num = parse_num(&line, &mut i);
            if second_num.is_none() {
                continue;
            }

            if !parse_char(&line, &mut i, ')') {
                continue;
            }

            let mul = first_num.unwrap() * second_num.unwrap();
            result += mul;

            if mul_enabled {
                result_2 += mul;
            }
        }
    }

    (result.to_string(), result_2.to_string())
}
