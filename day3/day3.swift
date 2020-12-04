import Foundation

print("This is a test.")

let file = "/advent-of-code-2020/day3/input.txt" //this is the file. we will write to and read from it

// TODO: Get this to be the current folder, not my documents folder.
if let dir = FileManager.default.urls(for: .documentDirectory, in: .userDomainMask).first {

    let fileURL = dir.appendingPathComponent(file)
    print(fileURL)

    //read from file
    do {
        let text = try String(contentsOf: fileURL, encoding: .utf8)
        print(text)
        
    } catch {
        print("Could not read file.")
    }

    
}