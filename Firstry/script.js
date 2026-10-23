const quizBank = {
  python: [
    { q: "Which Python data type stores items as key–value pairs?", options: ["List", "Dictionary", "Tuple", "Set"], answer: 1, explanation: "A dictionary maps unique keys to values, for example: { name: 'Asha', score: 95 }." },
    { q: "What does the len() function return?", options: ["The last item", "The item type", "The number of items", "A sorted list"], answer: 2, explanation: "len() returns the number of elements in an object, such as a list, string, or dictionary." },
    { q: "Which keyword defines a function in Python?", options: ["function", "def", "func", "define"], answer: 1, explanation: "Python functions are declared using def, followed by the function name and parentheses." },
    { q: "What is the result of 3 ** 2 in Python?", options: ["6", "9", "8", "5"], answer: 1, explanation: "The ** operator performs exponentiation, so 3 ** 2 means 3 squared, or 9." },
    { q: "Which statement is used to handle errors in Python?", options: ["try / except", "check / catch", "if / else", "error / handle"], answer: 0, explanation: "Use a try block for code that may fail and except to handle an expected error." }
  ],
  "machine learning": [
    { q: "What is supervised learning trained with?", options: ["Only random data", "Labelled examples", "No data", "A fixed rule book"], answer: 1, explanation: "Supervised learning uses input data paired with known target labels." },
    { q: "Which task is a classification problem?", options: ["Predicting house price", "Grouping similar customers", "Identifying an email as spam", "Reducing file size"], answer: 2, explanation: "Classification predicts a category; spam or not spam is a common binary classification example." },
    { q: "What does overfitting mean?", options: ["The model is too small", "The model memorises training data and generalises poorly", "The data has no labels", "The model trains too slowly"], answer: 1, explanation: "An overfit model performs well on training data but poorly on unseen examples." },
    { q: "Why is a test set used?", options: ["To train the model", "To tune every parameter", "To estimate performance on unseen data", "To remove missing values"], answer: 2, explanation: "A held-out test set gives a more honest estimate of real-world model performance." },
    { q: "Which metric is especially useful when classes are imbalanced?", options: ["Accuracy only", "Precision and recall", "Screen size", "Learning rate"], answer: 1, explanation: "Precision and recall help show how well a classifier handles the minority class." }
  ],
  genai: [
    { q: "What does a large language model primarily predict?", options: ["The next token", "A database row", "A computer password", "A network cable"], answer: 0, explanation: "LLMs generate text by predicting likely next tokens from the context they receive." },
    { q: "What is a prompt?", options: ["A GPU chip", "Instructions or context given to a model", "A programming language", "A model error"], answer: 1, explanation: "A prompt is the input that guides the model's response, such as a question, examples, or constraints." },
    { q: "What is hallucination in generative AI?", options: ["A verified citation", "A model creating incorrect but plausible content", "A faster model response", "A type of encryption"], answer: 1, explanation: "A hallucination is an output that sounds convincing but is unsupported or false, so important claims need checking." },
    { q: "What is the purpose of retrieval-augmented generation (RAG)?", options: ["To remove all prompts", "To ground responses in retrieved information", "To turn text into images only", "To make a model smaller"], answer: 1, explanation: "RAG supplies relevant documents as context, helping models answer with up-to-date or private information." },
    { q: "Which practice improves a prompt for a structured response?", options: ["Avoiding all details", "Adding a clear output format and constraints", "Using only one word", "Removing the task"], answer: 1, explanation: "Specifying the task, context, tone, and desired format makes model output more reliable." }
  ]
};

const skillLibrary = [
  "python", "java", "javascript", "typescript", "html", "css", "react", "angular", "node.js", "sql", "mysql", "postgresql", "mongodb", "excel", "power bi", "tableau", "machine learning", "deep learning", "data analysis", "data science", "generative ai", "genai", "llm", "nlp", "aws", "azure", "docker", "kubernetes", "git", "github", "figma", "agile", "scrum", "communication", "leadership", "project management", "c++", "c#", "tensorflow", "pytorch", "flask", "django"
];

const tabs = document.querySelectorAll(".tab");
tabs.forEach(tab => tab.addEventListener("click", () => {
  tabs.forEach(item => item.classList.remove("active"));
  document.querySelectorAll(".tool-panel").forEach(panel => panel.classList.remove("active-panel"));
  tab.classList.add("active");
  document.getElementById(tab.dataset.panel).classList.add("active-panel");
}));

const normalizeTopic = topic => {
  const value = topic.toLowerCase().trim();
  if (value.includes("python")) return "python";
  if (value.includes("machine") || value === "ml") return "machine learning";
  if (value.includes("genai") || value.includes("generative") || value.includes("llm")) return "genai";
  return "python";
};

document.getElementById("quiz-setup").addEventListener("submit", event => {
  event.preventDefault();
  const topicInput = document.getElementById("topic");
  const requestedTopic = topicInput.value.trim() || "Python";
  const topic = normalizeTopic(requestedTopic);
  const count = Number(document.getElementById("question-count").value);
  const difficulty = document.getElementById("difficulty").value;
  const questions = [...quizBank[topic]].sort(() => Math.random() - .5).slice(0, count);
  showQuiz(questions, requestedTopic, difficulty);
});

function showQuiz(questions, topic, difficulty) {
  const content = document.getElementById("quiz-content");
  document.getElementById("quiz-empty").classList.add("hidden");
  content.classList.remove("hidden");
  content.innerHTML = `<div class="quiz-intro"><strong>${escapeHtml(topic)}</strong> · ${capitalize(difficulty)} · ${questions.length} questions</div>` + questions.map((question, qIndex) => `
    <article class="quiz-card" data-question="${qIndex}">
      <span class="question-number">QUESTION ${qIndex + 1}</span>
      <div class="question-text">${question.q}</div>
      <div class="options">${question.options.map((option, optionIndex) => `<button class="option" data-option="${optionIndex}">${String.fromCharCode(65 + optionIndex)}. ${option}</button>`).join("")}</div>
      <p class="explanation"><strong>Explanation:</strong> ${question.explanation}</p>
    </article>`).join("") + `<div id="quiz-result-slot"></div>`;

  let answered = 0;
  let score = 0;
  content.querySelectorAll(".quiz-card").forEach((card, qIndex) => {
    card.querySelectorAll(".option").forEach(button => button.addEventListener("click", () => {
      if (card.dataset.answered) return;
      card.dataset.answered = "true";
      const selected = Number(button.dataset.option);
      const correct = questions[qIndex].answer;
      card.querySelectorAll(".option").forEach(option => {
        option.disabled = true;
        if (Number(option.dataset.option) === correct) option.classList.add("reveal-correct");
      });
      button.classList.remove("reveal-correct");
      if (selected === correct) { score++; button.classList.add("selected-correct"); }
      else button.classList.add("selected-wrong");
      card.querySelector(".explanation").classList.add("show");
      answered++;
      if (answered === questions.length) showScore(score, questions.length);
    }));
  });
  content.scrollIntoView({ behavior: "smooth", block: "start" });
}

function showScore(score, total) {
  const percent = Math.round(score / total * 100);
  const message = percent === 100 ? "Excellent work — perfect score!" : percent >= 60 ? "Nice work — keep building your knowledge." : "Good start — review the explanations and try again.";
  document.getElementById("quiz-result-slot").innerHTML = `<div class="result-card"><div class="score">${score}/${total}</div><p>${message}</p><button class="secondary-button" onclick="document.getElementById('quiz-setup').requestSubmit()">Try another quiz</button></div>`;
}

document.getElementById("matcher-form").addEventListener("submit", event => {
  event.preventDefault();
  const resume = document.getElementById("resume-text").value.toLowerCase();
  const job = document.getElementById("job-text").value.toLowerCase();
  const jobSkills = skillLibrary.filter(skill => includesSkill(job, skill));
  const matching = jobSkills.filter(skill => includesSkill(resume, skill));
  const missing = jobSkills.filter(skill => !includesSkill(resume, skill));
  const score = jobSkills.length ? Math.round(matching.length / jobSkills.length * 100) : calculateWordOverlap(resume, job);
  showMatchResults(score, matching, missing, jobSkills.length);
});

function includesSkill(text, skill) {
  const escaped = skill.replace(/[.*+?^${}()|[\]\\]/g, "\\$&");
  return new RegExp(`(^|[^a-z0-9+#.])${escaped}(?=$|[^a-z0-9+#.])`, "i").test(text);
}

function calculateWordOverlap(resume, job) {
  const ignored = new Set(["with", "this", "that", "from", "will", "have", "your", "and", "the", "for", "our", "you", "are", "job", "role", "years", "experience", "work"]);
  const jobWords = [...new Set(job.match(/[a-z]{4,}/g) || [])].filter(word => !ignored.has(word));
  const overlap = jobWords.filter(word => resume.includes(word));
  return jobWords.length ? Math.min(95, Math.round(overlap.length / jobWords.length * 100)) : 0;
}

function showMatchResults(score, matching, missing, recognisedSkills) {
  const results = document.getElementById("match-results");
  const empty = document.getElementById("match-empty");
  empty.classList.add("hidden");
  results.classList.remove("hidden");
  const summary = score >= 75 ? "You are a strong match for this role." : score >= 45 ? "You have a solid base, with a few gaps to address." : "There are clear opportunities to tailor your resume.";
  const generalHint = recognisedSkills ? "Add missing skills only when you genuinely have learned or used them." : "Use the exact keywords and responsibilities from the job description throughout your experience bullets.";
  results.innerHTML = `
    <div class="match-summary"><div class="score-circle">${score}%</div><div><h3>Your match score</h3><p>${summary} This estimate compares recognised role skills and relevant keywords.</p></div></div>
    <div class="skill-columns">
      <article class="skill-box matching"><h3>✓ Matching skills</h3><div class="chips">${renderChips(matching, "good", "No matching library skills found yet.")}</div></article>
      <article class="skill-box missing"><h3>+ Skills to develop</h3><div class="chips">${renderChips(missing, "missing", "Great — no recognised skill gaps.")}</div></article>
    </div>
    <article class="suggestions"><h3>Resume suggestions</h3><ul>
      <li>Place your most relevant skills and projects near the top of your resume.</li>
      <li>${generalHint}</li>
      <li>Turn responsibilities into results with action verbs and measurable outcomes.</li>
      ${missing.length ? `<li>For this role, consider learning or demonstrating: <strong>${missing.slice(0, 3).join(", ")}.</strong></li>` : ""}
    </ul></article>`;
  results.scrollIntoView({ behavior: "smooth", block: "start" });
}

function renderChips(skills, type, emptyMessage) {
  return skills.length ? skills.map(skill => `<span class="chip ${type}">${escapeHtml(skill)}</span>`).join("") : `<span class="no-skills">${emptyMessage}</span>`;
}
function capitalize(value) { return value.charAt(0).toUpperCase() + value.slice(1); }
function escapeHtml(value) { const node = document.createElement("span"); node.textContent = value; return node.innerHTML; }

/*
  OPTIONAL LLM INTEGRATION:
  Replace the local quizBank lookup with a fetch request to your own secure backend.
  Do not place an API key in this browser file. Your backend can call an LLM with:
  "Create 5 {difficulty} MCQs on {topic}. Return JSON with q, options, answer, explanation."
*/
