// Application Windows de TrameErgo : la même application que sur tablette,
// dans une fenêtre WebView2. Seul ajout : enregistrer le bilan dans
// Documents\TrameErgo et l'ouvrir dans Word (plugins fs et opener).
#[cfg_attr(mobile, tauri::mobile_entry_point)]
pub fn run() {
    tauri::Builder::default()
        .plugin(tauri_plugin_fs::init())
        .plugin(tauri_plugin_opener::init())
        .run(tauri::generate_context!())
        .expect("TrameErgo n'a pas pu démarrer");
}
