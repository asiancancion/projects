//
//  AddRecipeView.swift
//  RecipeSaver
//
//  Created by Caleb Song on 10/20/24.
//

import SwiftUI
import SwiftData
import PhotosUI

struct AddRecipeView: View{
//    @EnvironmentObject var recipesVM: RecipesViewModel
//    @Binding var recipes: [Recipe]
    @Environment(\.modelContext) private var context
    @Query private var recipes: [RecipeItem]
    
    @State private var name: String = ""
    @State private var selectedCategory: Category = Category.main
    @State private var recipeDescription: String = ""
    @State private var ingredients: String = ""
    @State private var directions: String = ""
    @State private var image: Data? = nil
    @State private var selectedItem: PhotosPickerItem? = nil
    @State private var isFavorite: Bool = false
    
    @Environment(\.dismiss) var dismiss
    
    var body: some View{
        NavigationView{
            Form{
                Section(header: Text("Name")){
                    TextField("Recipe Name", text: $name)
                }
                Section(header: Text("Category")){
                    Picker("Category", selection: $selectedCategory){
                        ForEach(Category.allCases){ category in
                            Text(category.rawValue)
                                .tag(category)
                        }
                    }
                    .pickerStyle(.menu)
                }
                Section(header: Text("Description")){
                    TextEditor(text: $recipeDescription)
                }
                Section(header: Text("Ingredients")){
                    TextEditor(text: $ingredients)
                }
                Section(header: Text("Directions")){
                    TextEditor(text: $directions)
                }
                
                Section(header: Text("Image")) {
                    // Display the selected image, or prompt the user to select one
                    if let image = image, let uiImage = UIImage(data: image) {
                        Image(uiImage: uiImage)
                            .resizable()
                            .scaledToFit()
                            .frame(height: 200)
                    } else {
                        Text("No Image Selected")
                    }
                    
                    PhotosPicker(
                        selection: $selectedItem,
                        matching: .images,
                        photoLibrary: .shared()) {
                            Text("Select Image")
                        }
                        .onChange(of: selectedItem) { newItem in
                            Task {
                                if let data = try? await newItem?.loadTransferable(type: Data.self) {
                                    image = data
                                }
                            }
                        }
                }
                Section (header: Text("Favorite")){
                    HStack {
                            Text("Mark as Favorite")
                            Spacer()
                            Button(action: {
                                isFavorite.toggle() // Toggle favorite status
                            }) {
                                Image(systemName: isFavorite ? "heart.fill" : "heart")
                                    .foregroundColor(isFavorite ? .red : .gray)
                                    .font(.title2)
                            }
                        }
                }
                
            }
            .toolbar(content:{
                ToolbarItem(placement: .navigationBarLeading){
                    Button{
                        dismiss()
                    }
                    label:{
                        Label("Cancel", systemImage: "xmark")
                            .labelStyle(.iconOnly)
                    }
                }
                
                ToolbarItem {
                    Button {
                        // Trigger recipe saving
                        saveRecipe()                    } label: {
                        Label("Done", systemImage: "checkmark")
                            .labelStyle(.iconOnly)
                    }
                    .disabled(name.isEmpty) // Disable Done button if name is empty
                }

            }

            )
            .navigationTitle("New Recipe")
            .navigationBarTitleDisplayMode(.inline)
           

        }
        .navigationViewStyle(.stack)
//        .sheet(isPresented: $navigateToRecipe) {
//                    if let lastRecipe = recipes.last {
//                        RecipeView(recipe: lastRecipe)
//                            .navigationBarBackButtonHidden(true)
//                    }
//                }
        

    }
    
}


struct AddRecipeView_Previews: PreviewProvider{
    @State static var recipes: [Recipe] = []
    static var previews: some View{
        AddRecipeView()
    }
}


extension AddRecipeView {
    private func saveRecipe(){
        let now = Date()
        
        let dateFormatter = DateFormatter()
        dateFormatter.dateFormat = "yyyy-MM-dd"
        
        let datePublished = dateFormatter.string(from: now)
        let recipe = RecipeItem(name: name, image: image, recipeDescription: recipeDescription, ingredients: ingredients, directions: directions, category: selectedCategory, datePublished: datePublished, favorite: isFavorite)
        
        context.insert(recipe)
        dismiss()
    }
}
